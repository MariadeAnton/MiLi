/*
fast_list: A minimal library that implements very high performant fast lists.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Gutson, FuDePAN 2010
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt in the root directory or 
    copy at http://www.boost.org/LICENSE_1_0.txt)
    
    MiLi IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#ifndef FAST_LIST_H
#define FAST_LIST_H

#include <new>
#include <list>

NAMESPACE_BEGIN

// Shrink Policies
struct NeverShrinkPolicy
{
    struct Node;

    struct Chunk
    {
        Chunk() {}
        Chunk(const Chunk&) {}

        bool empty() const
        {
            return false;
        }

        enum { NEED_INIT_NODES = false };

        void init_node(Node&) {}
        void mark_unused() {}
    };

    struct Node
    {
        void create() {}
        void destroy() {}
    };

    void init_chunk(Chunk&) {}
    enum { NEED_INIT_CHUNKS = false };
    enum { SHRINK_ENABLED = false };
    enum { NEED_NOTIFY_EMPTY_CHUNKS = false };
    enum { SHRINK_ON_CLEAR = false };

    void shrink()           {}
    bool shrinkable() const
    {
        return false;
    }
};

struct ShrinkOnRequestPolicy
{
    struct Node;

    struct Chunk
    {
        size_t used_count;

        Chunk() {}
        Chunk(const Chunk&) : used_count(0) {}

        bool empty() const
        {
            return used_count == 0;
        }

        enum { NEED_INIT_NODES = true };

        inline void init_node(Node& n);

        void mark_unused()
        {
            used_count = 0;
        }
    };

    struct Node
    {
        Chunk* chunk;
        void create()
        {
            ++chunk->used_count;
        }

        void destroy()
        {
            --chunk->used_count;
        }
    };

    void init_chunk(Chunk&)    {}

    enum { NEED_INIT_CHUNKS = false };
    enum { SHRINK_ENABLED = true };
    enum { NEED_NOTIFY_EMPTY_CHUNKS = true };
    enum { SHRINK_ON_CLEAR = false };

    void shrink()           {}
    bool shrinkable() const
    {
        return true;
    }
};

inline void ShrinkOnRequestPolicy::Chunk::init_node(ShrinkOnRequestPolicy::Node& node)
{
    node.chunk = this;
}

struct ShrinkOnClearPolicy : ShrinkOnRequestPolicy
{
    enum { NEED_NOTIFY_EMPTY_CHUNKS = false };
    enum { SHRINK_ON_CLEAR = true };
};

// This policy minimizes uneeded shrinks by having a flag that is turned on
// when there are empty chunks.
struct OptimizedShrinkOnRequestPolicy : ShrinkOnRequestPolicy
{
    bool empty_chunks;
    OptimizedShrinkOnRequestPolicy() : empty_chunks(false) {}

    struct Node;

    struct Chunk
    {
        size_t used_count;
        OptimizedShrinkOnRequestPolicy* policy;

        Chunk() {}
        Chunk(const Chunk&) : used_count(0) {}

        bool empty() const
        {
            return used_count == 0;
        }

        enum { NEED_INIT_NODES = true };

        inline void init_node(Node& n);

        void inc_nodes()
        {
            ++used_count;
        }

        void dec_nodes()
        {
            --used_count;
            if (used_count == 0)
                policy->empty_chunks = true;
        }

        void mark_unused()
        {
            used_count = 0;
            policy->empty_chunks = true;
        }
    };

    struct Node
    {
        Chunk* chunk;
        void create()
        {
            chunk->inc_nodes();
        }

        void destroy()
        {
            chunk->dec_nodes();
        }
    };

    void init_chunk(Chunk& chunk)
    {
        chunk.policy = this;
    }

    enum { NEED_INIT_CHUNKS = true };
    enum { NEED_NOTIFY_EMPTY_CHUNKS = true };

    void shrink()
    {
        empty_chunks = false;
    }

    bool shrinkable() const
    {
        return empty_chunks;
    }
};
inline void OptimizedShrinkOnRequestPolicy::Chunk::init_node(OptimizedShrinkOnRequestPolicy::Node& node)
{
    node.chunk = this;
}

// Type Hints
struct RegularTypeHints
{
    enum { CALL_DESTRUCTOR = false };
};

struct CustomTypeHints
{
    enum { CALL_DESTRUCTOR = true };
};

template <bool IsBasicType> // case TRUE
struct _HintsMapper
{
    typedef RegularTypeHints Hints;
};

template <>
struct _HintsMapper<false>
{
    typedef CustomTypeHints Hints;
};

template <class T>
struct DefaultHints
{
    typedef typename _HintsMapper <
    template_info<T>::is_native  ||
    template_info<T>::is_pointer ||
    template_info<T>::is_reference
    >::Hints Hints;
};

// MoveOnDestroy policies
struct InvalidateAfterDestroy
{
    template <class T>
    static T move(T, T)
    {
        return NULL;
    }
};

struct MoveNextAfterDestroy
{
    template <class T>
    static T move(T prev, T next)
    {
        return next;
    }
};

struct MovePrevAfterDestroy
{
    template <class T>
    static T move(T prev, T next)
    {
        return prev;
    }
};

struct MoveNextOrPrevAfterDestroy
{
    template <class T>
    static T move(T prev, T next)
    {
        return next != NULL ? next : prev;
    }
};

struct MovePrevOrNextAfterDestroy
{
    template <class T>
    static T move(T prev, T next)
    {
        return prev != NULL ? prev : next;
    }
};

template < class T,
         class ShrinkPolicy = NeverShrinkPolicy,
         class TypeHints = typename DefaultHints<T>::Hints,
         size_t CHUNK_SIZE = 10 >
class FastList
{
    struct Node;

    struct PhysicalList
    {
        Node*   first;
        Node*   last;

        PhysicalList() : first(NULL), last(NULL) {}

        bool empty() const
        {
            return first == NULL;
        }
    };

    struct SizedPhysicalList : PhysicalList
    {
        size_t  count;
        SizedPhysicalList() : PhysicalList(), count(0) {}
    };

    typedef char Placeholder[sizeof(T)];

    struct Node : ShrinkPolicy::Node
    {
        Node*       previous;
        Node*       next;
        Placeholder placeholder;

        T& get_data()
        {
            return *reinterpret_cast<T*>(&placeholder[0]);
        }

        const T& get_data() const
        {
            return *reinterpret_cast<const T*>(&placeholder[0]);
        }

        void destroy()
        {
            if (TypeHints::CALL_DESTRUCTOR)
                get_data().~T();

            ShrinkPolicy::Node::destroy();
        }

        void make_last()
        {
            next = NULL;
        }

        void make_first()
        {
            previous = NULL;
        }

        bool is_last() const
        {
            return next == NULL;
        }

        bool is_first() const
        {
            return previous == NULL;
        }

        void link_next(Node* new_next)
        {
            next = new_next;
            if (new_next != NULL)
                new_next->previous = this;
        }

        void link_previous(Node* new_prev)
        {
            previous = new_prev;
            if (new_prev != NULL)
                new_prev->next = this;
        }

        void detach_from_list(PhysicalList& old_list) // this is for implementation reasons. Assumes that the node belongs to this list.
        {
            if (is_first())
                old_list.first = next;
            else    // update my prev neighbor
                previous->link_next(next);

            if (is_last())
                old_list.last = previous;
            else    // update my next neighbor
                next->link_previous(previous);
        }

        void attach_to_list(PhysicalList& new_list)
        {
            if (new_list.empty())
            {
                make_first();
                new_list.first = new_list.last = this;
            }
            else
            {
                link_previous(new_list.last);
                new_list.last = this;
            }

            make_last();
        }

        void migrate_sublist(PhysicalList& old_list, PhysicalList& new_list)
        {
            Node* const last = old_list.last;

            //go out from old_list:
            old_list.last = previous;
            if (is_first())
                old_list.first = NULL;

            // attach to new_list:
            if (new_list.empty())
                new_list.first = this;

            link_previous(new_list.last);
            new_list.last = last;
        }
    };

    struct Chunk : ShrinkPolicy::Chunk
    {
        Node    nodes[CHUNK_SIZE];

        // do nothing here
        Chunk()
        {}

        // node 0 is for immediate use. Nodes 1..CHUNK_SIZE-1 are free.
        Chunk(const Chunk& other) : ShrinkPolicy::Chunk(other)
        {
            if (ShrinkPolicy::Chunk::NEED_INIT_NODES)
            {
                for (size_t i = 0; i < CHUNK_SIZE; ++i)
                    this->init_node(nodes[i]);
            }

            if (CHUNK_SIZE > 1)
            {
                for (size_t i = 1; i < (CHUNK_SIZE - 1); ++i)
                    nodes[i].link_next(&nodes[i + 1]);

                nodes[1].make_first();
                nodes[CHUNK_SIZE - 1].make_last();
            }
        }
    };

    PhysicalList        empty_nodes;
    SizedPhysicalList   used_nodes;
    std::list<Chunk>    chunks;
    ShrinkPolicy        shrink_policy;

    Node* allocate_node()
    {
        Node* ret;
        if (empty_nodes.empty())
        {
            // allocate new chunk:
            chunks.push_back(Chunk());
            Chunk& new_chunk = chunks.back();
            if (ShrinkPolicy::NEED_INIT_CHUNKS)
                shrink_policy.init_chunk(new_chunk);

            ret = &new_chunk.nodes[0];
            if (CHUNK_SIZE > 1)
            {
                empty_nodes.first = &new_chunk.nodes[1];
                empty_nodes.last  = &new_chunk.nodes[CHUNK_SIZE - 1];
            }
        }
        else
        {
            ret = empty_nodes.last;
            ret->detach_from_list(empty_nodes);
        }

        ret->create();
        ret->make_last();
        ret->attach_to_list(used_nodes);

        ++used_nodes.count;

        return ret;
    }
public:
    template <class NodePtr>
    class BasicHandler
    {
    protected:
        NodePtr node;
    public:
        BasicHandler()
            : node(NULL)
        {}

        BasicHandler(NodePtr node)
            : node(node)
        {}

        BasicHandler(const BasicHandler<NodePtr>& other)
            : node(other.node)
        {}

        BasicHandler<NodePtr>& operator = (const BasicHandler& other)
        {
            node = other.node;
            return *this;
        }

        const T& operator*() const
        {
            return node->get_data();
        }

        const T& operator ->() const
        {
            return operator*();
        }

        bool is_last() const
        {
            return node->is_last();
        }

        bool is_first() const
        {
            return node->is_first();
        }

        BasicHandler<NodePtr>& operator++()
        {
            node = node->next;
            return *this;
        }

        BasicHandler<NodePtr>& operator--()
        {
            node = node->previous;
            return *this;
        }

        BasicHandler<NodePtr> operator++(int)
        {
            BasicHandler<NodePtr> ret(*this);
            operator++();
            return ret;
        }

        BasicHandler<NodePtr> operator--(int)
        {
            BasicHandler<NodePtr> ret(*this);
            operator--();
            return ret;
        }

        bool is_valid() const
        {
            return node != NULL;
        }
    };

    typedef BasicHandler<const Node*> ConstElementHandler;

    class ElementHandler : public BasicHandler<Node*>
    {
    public:
        ElementHandler()
            : BasicHandler<Node*>(NULL)
        {}

        ElementHandler(Node* node)
            : BasicHandler<Node*>(node)
        {}

        ElementHandler(const ElementHandler& other)
            : BasicHandler<Node*>(other)
        {}

        ElementHandler& operator = (const ElementHandler& other)
        {
            BasicHandler<Node*>::operator=(other);
            return *this;
        }

        T& operator*()
        {
            return this->node->get_data();
        }

        T& operator ->()
        {
            return operator*();
        }
    };

    class _RemovableElementHandler : public ElementHandler
    {
    protected:
        PhysicalList*       empty_nodes_list;
        SizedPhysicalList*  used_nodes_list;
    public:
        _RemovableElementHandler()
            : ElementHandler(), empty_nodes_list(NULL), used_nodes_list(NULL)
        {}

        _RemovableElementHandler(Node* node, PhysicalList* empty_nodes_list, SizedPhysicalList* used_nodes_list)
            : ElementHandler(node), empty_nodes_list(empty_nodes_list), used_nodes_list(used_nodes_list)
        {}

        _RemovableElementHandler(const _RemovableElementHandler& other)
            : ElementHandler(other),
              empty_nodes_list(other.empty_nodes_list),
              used_nodes_list(other.used_nodes_list)
        {}

        _RemovableElementHandler& operator = (const _RemovableElementHandler& other)
        {
            ElementHandler::operator=(other);
            empty_nodes_list = other.empty_nodes_list;
            used_nodes_list = other.used_nodes_list;
            return *this;
        }
    };

    template <class MoveOnDestroyPolicy>
    class PRemovableElementHandler : public _RemovableElementHandler
    {
    public:
        bool destroy()
        {
            Node* const new_node = MoveOnDestroyPolicy::move(this->node->previous, this->node->next);
            this->node->detach_from_list(*this->used_nodes_list);
            this->node->attach_to_list(*this->empty_nodes_list);
            this->node->destroy();
            this->node = new_node;
            --this->used_nodes_list->count;
            return this->is_valid();
        }

        PRemovableElementHandler() {}

        PRemovableElementHandler(const _RemovableElementHandler& other)
            : _RemovableElementHandler(other)
        {}

        //PRemovableElementHandler(const PRemovableElementHandler<Mo& other)
        //    : _RemovableElementHandler(other)
        //{}

        PRemovableElementHandler<MoveOnDestroyPolicy>& operator = (const _RemovableElementHandler& other)
        {
            _RemovableElementHandler::operator=(other);
            return *this;
        }
    };
    typedef PRemovableElementHandler<InvalidateAfterDestroy> RemovableElementHandler;

    template <class Constructor>
    _RemovableElementHandler new_node_generic(Constructor& c)
    {
        Node* node = allocate_node();
        c(node->get_data());
        return _RemovableElementHandler(node, &empty_nodes, &used_nodes);
    }

    _RemovableElementHandler new_node() // default constructor
    {
        Node* node = allocate_node();
        new(&node->get_data()) T();
        return _RemovableElementHandler(node, &empty_nodes, &used_nodes);
    }

    _RemovableElementHandler new_node(const T& other) // copy constructor
    {
        Node* node = allocate_node();
        new(&node->get_data()) T(other);
        return _RemovableElementHandler(node, &empty_nodes, &used_nodes);
    }

    void shrink()
    {
        if (ShrinkPolicy::SHRINK_ENABLED && shrink_policy.shrinkable())
        {
            for (typename std::list<Chunk>::iterator it = chunks.begin();
                    it != chunks.end();
                    ++it)
            {
                if (it->empty())
                {
                    // assume all the nodes belong to the empty list:
                    for (size_t i = 0; i < CHUNK_SIZE; ++i)
                        it->nodes[i].detach_from_list(empty_nodes);

                    it = chunks.erase(it);
                }
            }
            shrink_policy.shrink();
        }
    }

    bool empty() const
    {
        return used_nodes.empty();
    }

    _RemovableElementHandler first()
    {
        return _RemovableElementHandler(used_nodes.first, &empty_nodes, &used_nodes);
    }

    ConstElementHandler first() const
    {
        return ConstElementHandler(used_nodes.first);
    }

    _RemovableElementHandler last()
    {
        return _RemovableElementHandler(used_nodes.last, &empty_nodes, &used_nodes);
    }

    ConstElementHandler last() const
    {
        return ConstElementHandler(used_nodes.last);
    }

    void clear()
    {
        if (!empty())
        {
            Node* n = used_nodes.first;

            if (!ShrinkPolicy::SHRINK_ON_CLEAR)
            {
                n->migrate_sublist(used_nodes, empty_nodes);
                if (ShrinkPolicy::NEED_NOTIFY_EMPTY_CHUNKS &&
                        !TypeHints::CALL_DESTRUCTOR)
                {
                    for (typename std::list<Chunk>::iterator it = chunks.begin();
                            it != chunks.end();
                            ++it)
                        it->mark_unused();
                }
            }

            if (TypeHints::CALL_DESTRUCTOR)
                do
                {
                    n->destroy();
                    n = n->next;
                }
                while (n != NULL);

            used_nodes.count = 0;
        }

        if (ShrinkPolicy::SHRINK_ON_CLEAR)
        {
            chunks.clear();
            empty_nodes.first = empty_nodes.last = NULL;
            shrink_policy.shrink();
        }
    }

    size_t size() const
    {
        return used_nodes.count;
    }

    ~FastList()
    {
        clear();
    }
};

NAMESPACE_END

#endif

