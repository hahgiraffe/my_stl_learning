/*
 * @Author: haha_giraffe
 * @Date: 2019-12-03 15:07:55
 * @Description: 红黑树的实现
 */
#ifndef MINISTL_SRC_CONTAINER_ASSOCIATIVE_RBTREE_H
#define MINISTL_SRC_CONTAINER_ASSOCIATIVE_RBTREE_H
#include "../../Iterator/stl_iterator.h"
#include "../../Allocator/allocator.h"
#include "../../Algorithm/algorithm.h"
#include <utility>

namespace MINISTL{

typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = false;
const __rb_tree_color_type __rb_tree_black = true;

//红黑树的基本节点
struct __rb_tree_node_base{
    typedef __rb_tree_color_type color_type;
    typedef __rb_tree_node_base* base_ptr;
    color_type color;   //节点颜色
    base_ptr parent;    //父节点指针
    base_ptr left;      //左子节点指针
    base_ptr right;     //右子节点指针

    //二叉搜索树一直往左走的最小值
    static base_ptr minimum(base_ptr x){
        while(x->left != 0) x = x->left;
        return x;
    }
    
    //二叉搜索树一直往右走的最大值
    static base_ptr maximum(base_ptr x){
        while(x->right != 0) x = x->right;
        return x;
    }
};

//这是红黑树节点
template <typename Value>
struct __rb_tree_node : public __rb_tree_node_base{
    typedef __rb_tree_node<Value>* link_type;
    Value value_field;  //值
};

//STL中红黑树采用的是和slist一样的双层迭代器架构
//双层迭代器架构的好处在于：某些函数（or 变量）不依赖于模板参数，所以把它提取到公共基类中，减少生成的重复代码，将模板与非模板分开，增加了使用的灵活性。

//基层迭代器
struct __rb_tree_base_iterator{
    typedef __rb_tree_node_base::base_ptr base_ptr;
    typedef bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t difference_type;

    base_ptr node;  //迭代器指向的节点
    //更改node使得其指向下一个值比其大的节点
    void increment(){
        if(node->right != 0){
            //当有右节点的时候，node指向右节点的最左子树节点
            node = node->right;
            while(node->left != 0){
                node = node->left;
            }
        }
        else{
            //没有右节点
            base_ptr y = node->parent;
            //如果当前节点为父节点的右子节点，就一直上溯
            while(node == y->right){
                node = y;
                y = y->parent;
            }
            //当node为y的左节点的时候，y就是可以返回的下一个节点，所以赋值即可
            if(node->right != y){
                node = y;
            }
        }
        //最后出来的时候node就是下一个节点
    }
    //更改node使得指向下一个值比起小的节点，思路和increment一样
    void decrement(){
        if(node->color == __rb_tree_red && node->parent->parent == node){
            node = node->right;
        }
        else if(node->left != 0){
            base_ptr y = node->left;
            while(y->right != 0){
                y = y->right;
            }
            node = y;
        }
        else{
            base_ptr y = node->parent;
            while(node == y->left){
                node = y;
                y = y->parent;
            }
            node = y;
        }
    }
};

//真正迭代器
template <typename Value, typename Ref, typename Ptr>
struct __rb_tree_iterator : __rb_tree_base_iterator{
    //这里要把型别写全面了
    typedef Value value_type;
    typedef Ref reference;
    typedef Ptr pointer;
    typedef __rb_tree_iterator<Value, Value&, Value*> iterator;
    typedef __rb_tree_iterator<Value, const Value&, const Value*> const_iterator;
    typedef __rb_tree_iterator<Value, Ref, Ptr> self;
    typedef __rb_tree_node<Value>* link_type;

    //ctor
    __rb_tree_iterator() { }
    __rb_tree_iterator(link_type x) {node = x; }
    __rb_tree_iterator(const iterator& it) { node = it.node; }

    //取迭代器所指节点的值
    reference operator*() const { return link_type(node)->value_field; }
    pointer operator-> () const { return &(operator*()); }
    self& operator++() { increment(); return *this;}
    self operator++(int) {
        self tmp = *this;
        increment();
        return tmp;
    }
    self& operator--() { decrement(); return *this;}
    self operator--(int) { 
        self tmp = *this;
        decrement();
        return tmp;
    }
};

//这里如果要rb_tree的iterator之间比较则可以转换成基类后比较
inline bool operator ==(const __rb_tree_base_iterator& itr1, const __rb_tree_base_iterator& itr2){
    return itr1.node == itr2.node;
}

inline bool operator !=(const __rb_tree_base_iterator& itr1, const __rb_tree_base_iterator& itr2){
    return itr1.node != itr2.node;
}



//注意这的五个模板参数，Key为类型，Value为键值对，KeyofValue为functor如何从Value中取键，Compare比较方法，Alloc分配器
template <typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc = __default_alloc>
class rb_tree{

protected:
    typedef void* void_pointer;
    typedef __rb_tree_node_base* base_ptr;
    typedef __rb_tree_node<Value> rb_tree_node;
    typedef allocator<rb_tree_node, Alloc> rb_tree_node_allocator;
    typedef __rb_tree_color_type color_type;

public:
    typedef Key key_type;
    typedef Value value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef rb_tree_node* link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef __rb_tree_iterator<value_type, reference, pointer> iterator;
    typedef __rb_tree_iterator<value_type, const reference, const pointer> const_iterator;
    

protected:
    //内存管理
    //申请内存
    link_type get_node() { return rb_tree_node_allocator::allocate(); }
    //释放内存
    void put_node(link_type p) { rb_tree_node_allocator::deallocate(p); }
    //新建节点（包括申请内存和初始化）
    link_type create_node(const value_type& x){
        link_type tmp = get_node();
        try
        {
            construct(&tmp->value_field, x);
        }
        catch(const std::exception& e)
        {
            put_node(tmp);
            std::cerr << e.what() << '\n';
        }
        return tmp;
    }
    //复制节点
    link_type clone_node(link_type x){
        link_type tmp = create_node(x->value_field);
        tmp->color = x->color;
        tmp->left = 0;
        tmp->right = 0;
        return tmp;
    }
    //销毁节点(包括析构和释放)
    void destroy_node(link_type p){
        destroy(&p->value_field);
        put_node(p);
    }

protected:
    size_type node_count;       //节点数量
    link_type header;           //header节点是一个新节点，其父节点指向根节点，左子节点指向最小节点，右子节点指向最大节点
    Compare key_compare;        //key_functor比较准则

    link_type& root() const { return (link_type&)header->parent; }
    link_type& leftmost() const { return (link_type&)header->left; }
    link_type& rightmost() const { return (link_type&)header->right; }

    static link_type& left(link_type x){
        return (link_type&)x->left;
    }
    static link_type& right(link_type x){
        return (link_type&)x->right;
    }
    static link_type& parent(link_type x){
        return (link_type&)x->parent;
    }
    static reference value(link_type x){
        return x->value_field;
    }
    static const Key& key(link_type x){
        return KeyofValue()(value(x));
    }
    static color_type& color(link_type x){
        return (color_type&)x->color;
    }

    static link_type& left(base_ptr x){
        return (link_type&)x->left;
    }
    static link_type& right(base_ptr x){
        return (link_type&)x->right;
    }
    static link_type& parent(base_ptr x){
        return (link_type&)x->parent;
    }
    static reference value(base_ptr x){
        return ((link_type)x)->value_field;
    }
    static const Key& key(base_ptr x){
        return KeyofValue()(value((link_type)x));
    }
    static color_type& color(base_ptr x){
        return (color_type&)(link_type(x)->color);
    }

    static link_type minimum(link_type x){
        return (link_type) __rb_tree_node_base::minimum(x);
    }
    static link_type maximum(link_type x){
        return (link_type) __rb_tree_node_base::maximum(x);
    }

private:
    iterator __insert(base_ptr x, base_ptr y, const value_type& v);
    link_type __copy(link_type x, link_type p);
    void __erase(link_type x);
    base_ptr __rb_tree_erase_balance(base_ptr position, base_ptr& parent, base_ptr& left, base_ptr& right);
    //初始化header节点
    void init(){
        header = get_node();                //申请header内存
        color(header) = __rb_tree_red;      //header节点设置为红    
        root() = 0;                         //header的父节点为0
        leftmost() = header;                //header左节点为自己
        rightmost() = header;               //header右节点为自己
    }

public:
    rb_tree(const Compare& comp = Compare())
        : node_count(0), key_compare(comp) { init(); }
    ~rb_tree(){
        clear();
        put_node(header);
    }

    rb_tree<Key, Value, KeyofValue, Compare, Alloc>& operator = (const rb_tree<Key, Value, KeyofValue, Compare, Alloc>& rhs){
        if(this == &rhs){
            return *this;
        }
        clear();
        node_count = 0;
        key_compare = rhs.key_compare;
        if(rhs.root()){
            root() = __copy(rhs.root(), header);
            leftmost() = minimum(root());
            rightmost() = maximum(root());
            node_count = rhs.node_count;
        }
        else{
            root() = NULL;
            leftmost() = header;
            rightmost() = header;
        }
        return *this;
    }

    Compare key_comp() const { return key_compare; }
    iterator begin() { return leftmost(); }
    iterator end() { return header; }
    bool empty() const {return node_count == 0; }
    size_type size() const { return node_count; }
    size_type max_size() const { return size_type(-1); }
    void swap(rb_tree<Key, Value, KeyofValue, Compare, Alloc>& rhs){
        MINISTL::swap(header, rhs.header);
        MINISTL::swap(leftmost(), rhs.leftmost());
        MINISTL::swap(rightmost(), rhs.rightmost());
    }
    std::pair<iterator, iterator> equal_range(const key_type& k);
    iterator lower_bound(const key_type& k);
    iterator upper_bound(const key_type& k);
    //insert_unique
    std::pair<iterator, bool> insert_unique(const value_type& x);
    template <typename InputIterator>
    void insert_unique(InputIterator first, InputIterator last);
    // iterator insert_unique(iterator position,const value_type& x);

    //insert_equal
    iterator insert_equal(const value_type& x);

    //erase
    void erase(iterator position);
    size_type erase(const key_type& x);
    void erase(iterator first, iterator last);

    iterator find(const Key& x);
    size_type count(const Key& x);

    //还没有实现
    void clear(){
        if(node_count != 0){
            __erase(root());
            root() = NULL;
            leftmost() = header;
            rightmost() = header;
            node_count = 0;
        }
    }
};


//表示插入的元素在树中可以重复
template <typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc>
typename rb_tree<Key, Value, KeyofValue, Compare, Alloc>::iterator 
rb_tree<Key, Value, KeyofValue, Compare, Alloc>::insert_equal(const Value& v){
    link_type y = header;
    link_type x = root();   //根节点
    while(x != 0){
        y = x;
        x = key_compare(KeyofValue()(v), key(x)) ? left(x) : right(x);  //比较插入的元素与当前节点比较
    }
    return __insert(x, y, v);   //x为新值插入点，y为插入点的父节点，v为插入的值
}

//表示插入的元素在树中独一无二
template <typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc>
std::pair<typename rb_tree<Key, Value, KeyofValue, Compare, Alloc>::iterator, bool> 
rb_tree<Key, Value, KeyofValue, Compare, Alloc>::insert_unique(const Value& v){
    link_type y = header;
    link_type x = root();
    bool comp = true;
    //找到插入位置
    while(x != 0){
        y = x;
        comp = key_compare(KeyofValue()(v), key(x));
        x = comp ? left(x) : right(x);
    }
    //y为插入位置的父节点，x为插入位置
    iterator j = iterator(y);
    if(comp){
        //comp为true表示最后一次判断为大于，则说明当前节点的插入位置在其父节点的左子树
        if( j == begin()){
            //如果父节点在最左节点
            return std::pair<iterator, bool> (__insert(x, y, v), true);
        }
        else{
            //父节点不在最左节点
            j--;    //调整j（调用operator -- (int)），指向比父节点值小的节点
        }
    }
    if(key_compare(key(j.node), KeyofValue()(v)) ){
        //新值不与当前存在的节点值重复则直接插入
        return std::pair<iterator, bool> (__insert(x, y, v), true);
    }
    //表示存在重复值则不插入
    return std::pair<iterator, bool>(j, false);
}

template <typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc>
template <typename InputIterator>
void rb_tree<Key, Value, KeyofValue, Compare, Alloc>::insert_unique(InputIterator first, InputIterator last){
    for(; first != last; ++first){
        insert_unique(*first);
    }
}



//x节点左旋，这个动作其实很经典的，可以好好参考里面的逻辑
inline void _rb_tree_rotate_left(__rb_tree_node_base* x, __rb_tree_node_base*& root){
    __rb_tree_node_base* y = x->right;      //y为旋转的右子节点
    x->right = y->left;
    if(y->left != 0){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x == root){
        root = y;
    }
    else if( x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

//x节点右旋，和上面的对称
inline void _rb_tree_rotate_right(__rb_tree_node_base* x, __rb_tree_node_base*& root){
    __rb_tree_node_base* y = x->left;      //y为旋转的左子节点
    x->left = y->right;
    if(y->right != 0){
        y->right->parent = x;
    }
    y->parent = x->parent;
    if(x == root){
        root = y;
    }
    else if( x == x->parent->right){
        x->parent->right = y;
    }
    else{
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
   
}

//插入节点后保持平衡，x是插入节点的位置，root表示根节点(*&表示函数传递的是指针的引用)
inline void __rb_tree_rebalance(__rb_tree_node_base* x, __rb_tree_node_base*& root){
    x->color = __rb_tree_red;   //设置新插入节点颜色为红
    while(x != root && x->parent->color == __rb_tree_red){
        //当插入节点的父亲节点为红色（若为黑色或为根节点直接退出循环）
        if(x->parent == x->parent->parent->left){
            //父节点为祖父节点的左节点
            __rb_tree_node_base* y = x->parent->parent->right;  //y为叔节点
            if(y && y->color == __rb_tree_red){
                //如果叔节点为红色（则此时祖父节点必为黑色），此时更改父亲、叔叔、祖父节点的颜色，同时设置祖父节点为要更改的节点
                x->parent->color = __rb_tree_black;
                y->color = __rb_tree_black;
                x->parent->parent->color = __rb_tree_red;
                x = x->parent->parent;
            }
            else{
                //没有叔节点或者叔节点为黑，此时又要分成两种情况进行考虑
                if(x ==  x->parent->right){
                    //如果插入节点为父节点的右子节点，此时为内插入，需要两次单旋，第一次为父节点左旋
                    x = x->parent;
                    _rb_tree_rotate_left(x, root);
                }
                //更改父亲节点和祖父节点颜色
                //注意一点，下面的代码同时适用于两种情况的
                x->parent->color = __rb_tree_black;
                x->parent->parent->color = __rb_tree_red;
                //右旋祖父节点
                _rb_tree_rotate_right(x->parent->parent, root);
            }
        }
        else{
            //父节点为祖父节点的右节点（其实是对称的）
            __rb_tree_node_base* y = x->parent->parent->left;  //y为叔节点
            if(y && y->color == __rb_tree_red){
                //同上
                x->parent->color = __rb_tree_black;
                y->color = __rb_tree_black;
                x->parent->parent->color = __rb_tree_red;
                x = x->parent->parent;
            }
            else{
                //没有叔节点或者叔节点为黑，此时又要分成两种情况进行考虑
                if(x ==  x->parent->left){
                    //如果插入节点为父节点的左子节点，此时为内插入，需要两次单旋，第一次为父节点右旋
                    x = x->parent;
                    _rb_tree_rotate_right(x, root);
                }
                //更改父亲节点和祖父节点颜色
                //注意一点，下面的代码同时适用于两种情况的
                x->parent->color = __rb_tree_black;
                x->parent->parent->color = __rb_tree_red;
                //左旋祖父节点
                _rb_tree_rotate_left(x->parent->parent, root);
            }
        }
    }
    root->color = __rb_tree_black;  //根节点为黑色
}

//真正执行的插入操作，x指向插入点，y指向插入点的父节点，x为插入的值
template <typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc>
typename rb_tree<Key, Value, KeyofValue, Compare, Alloc>::iterator 
rb_tree<Key, Value, KeyofValue, Compare, Alloc>::__insert(base_ptr x__, base_ptr y__, const Value& v){
    link_type x = (link_type) x__;
    link_type y = (link_type) y__;
    link_type z;
    if(y == header || x != 0 || key_compare(KeyofValue()(v), key(y))){
        //在父节点的左子树插入
        z = create_node(v);
        left(y) = z;
        if(y == header){
            //如果父节点是header说明当前树为空，新增节点设置为root
            root() = z;
            rightmost() = z;
        }
        else if(y == leftmost()){
            //如果父节点是最左节点，则更新header的最左节点
            leftmost() = z;
        }
    }
    else{
        //在父节点的右子树插入
        z = create_node(v);
        right(y) = z;
        if(y == rightmost()){
            //如果父节点是最右节点，则更新header的最右节点
            rightmost() = z;
        }
    }
    //设置插入节点的parent，left，right
    parent(z) = y;
    left(z) = 0;
    right(z) = 0;
    //调整红黑树使其再次平衡
    __rb_tree_rebalance(z, header->parent);//z为新增节点，header->parent为root节点
    ++node_count;
    return iterator(z);
}

//红黑树中查找，这里的技巧在于，key_compare只能表示 < 为true，但是可以找到 = ，且还可以找到红黑树中是否有这个值
template <typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc>
typename rb_tree<Key, Value, KeyofValue, Compare, Alloc>::iterator 
rb_tree<Key, Value, KeyofValue, Compare, Alloc>::find(const Key& k){
    link_type y = header;   //y指向不小于k的最后一个元素(y >= k)
    link_type x = root();   //x遍历
    while(x){
        if( !key_compare(key(x), k)){
            //这里是x的值不小于k
            y = x;
            x = left(x);
        }
        else{
            x = right(x);
        }
    }
    iterator j = iterator(y);
    //当j == end()表示没有找到, key_compare(k, key(j.node))表示 k < j(y) ，当这个条件不满足的时候即 k >= j(y) ，又因为前面条件是y >= k ，所以最后得到 y == k
    return  (j == end()) || key_compare(k, key(j.node)) ? end() : j;
}


template <typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc>
typename rb_tree<Key, Value, KeyofValue, Compare, Alloc>::size_type 
rb_tree<Key, Value, KeyofValue, Compare, Alloc>::count(const Key& x){
    std::pair<iterator, iterator> itr = equal_range(x);
    return MINISTL::distance(itr.first, itr.second);
}


//红黑树的拷贝，用于operator =
template <typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc>
typename rb_tree<Key, Value, KeyofValue, Compare, Alloc>::link_type 
rb_tree<Key, Value, KeyofValue, Compare, Alloc>::__copy(link_type from, link_type h){
    link_type top = clone_node(from);
    top->parent = h;
    try
    {
        if(from->right){
            top->right = __copy(right(from), top);
        }
        h = top;
        from = left(from);
        while (from) {
            link_type p = clone_node(from);
            h->left = p;
            p->parent = h;
            if (from->right)
                p->right = __copy(right(from), p);
            h = p;
            from = left(from);
        }
    }
    catch(const std::exception& e)
    {
        __erase(top);
        std::cerr << e.what() << '\n';
    }
    return top;
}

//删除itr的所有子树，__erase(root())就是删除整个树
template <typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc>
void rb_tree<Key, Value, KeyofValue, Compare, Alloc>::__erase(link_type itr){
    //递归删除节点
    while(itr){
        __erase(right(itr));
        link_type l = left(itr);
        destroy_node(itr);
        itr = l;
    }
}




//删除并调整，删除的先定位，再调整
template <typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc>
typename rb_tree<Key, Value, KeyofValue, Compare, Alloc>::base_ptr 
rb_tree<Key, Value, KeyofValue, Compare, Alloc>::__rb_tree_erase_balance(base_ptr position, base_ptr& root, base_ptr& leftmost, base_ptr& rightmost){
    //首先判断要删除的节点有没有子节点
    base_ptr y = position;
    base_ptr x = NULL;
    base_ptr x_parent = NULL;
    if(!y->left){
        //如果被删除的节点没有左孩子则直接移动到右孩子
        x = y->right;
    }
    else if(!y->right){
        //如果被删除的节点没有右孩子则直接移动到左孩子
        x = y->left;
    }
    else{
        //被删除节点的左右孩子都存在，则寻找后继节点
        y = y->right;
        while(y->left){
            y = y->left;
        }
        x = y->right;
    }
    if(y != position) {
        // 若条件成立，此时y为position的后代,即上面的第三种情况
        position->left->parent = y;
        y->left = position->left;
        if(y != position->right) {
            x_parent = y->parent;
            if(x){
                x->parent = y->parent;
            }
            y->parent->left = x;
            y->right = position->right;
            position->right->parent = y;
        }
        else{
            x_parent = y;
        }
        if(root == position)
            root = y;
        else if(position->parent->left == position)
            position->parent->left = y;
        else
            position->parent->right = y;
        y->parent = position->parent;
        MINISTL::swap(y->color, position->color);
        y = position;
    }
    else {
        //这里是被删除的节点只有一个子节点，接下来进行替换
        x_parent = y->parent;
        if(x)
            x->parent = y->parent;
        if(root == position)
            root = x;
        else if(position->parent->left == position)
            position->parent->left = x;
        else
            position->parent->right = x;
        if(leftmost == position)
            if(!position->right)
                leftmost = position->parent;
            else
                leftmost = __rb_tree_node_base::minimum(x);
        if(rightmost == position)
            if(!position->left)
                rightmost = position->parent;
            else
                rightmost = __rb_tree_node_base::maximum(x);
    }
    // 位置找到后，接下来进行调整。如果删除的节点是红色则不需要调整；如果删除的节点是黑色且为根节点也不需要调整
    if(y->color != __rb_tree_red){
        while( x != root && (!x || x->color == __rb_tree_black)){
            if(x == x->parent->left){
                //如果该节点是父节点的左子节点,w为兄弟节点
                base_ptr w = x_parent->right;
                if (w->color == __rb_tree_red) {
                    //如果兄弟节点是红色（此时父节点与兄弟节点的子节点都是黑色）  情况1
                    w->color = __rb_tree_black;
                    x_parent->color = __rb_tree_red;
                    _rb_tree_rotate_left(x_parent, root);
                    w = x_parent->right;
                }
                if ((!w->left || w->left->color == __rb_tree_black) &&
                    (!w->right || w->right->color == __rb_tree_black)) {
                    //兄弟节点为黑色，且兄弟节点的子节点都为黑色                情况2
                    w->color = __rb_tree_red;
                    x = x_parent;
                    x_parent = x_parent->parent;
                }
                else {
                    //兄弟节点是黑色
                    if (!w->right || w->right->color == __rb_tree_black) {
                        //兄弟节点右孩子是黑色                              情况3
                        if (w->left)
                            w->left->color = __rb_tree_black;
                        w->color = __rb_tree_red;
                        _rb_tree_rotate_right(w, root);
                        w = x_parent->right;
                    }
                    //兄弟节点的右孩子是红色                                 情况4
                    w->color = x_parent->color;
                    x_parent->color = __rb_tree_black;
                    if (x->right)
                        w->right->color = __rb_tree_black;
                    _rb_tree_rotate_left(x_parent, root);
                    break;
                }
            }
            else{
                //如果该节点是父节点的右子节点，和上面的情况对称
                base_ptr w = x_parent->left;
                if (w->color == __rb_tree_red) {
                    w->color = __rb_tree_black;
                    x_parent->color = __rb_tree_red;
                    _rb_tree_rotate_right(x_parent, root);
                    w = x_parent->left;
                }
                if ((!w->right || w->right->color == __rb_tree_black) &&
                    (!w->left || w->left->color == __rb_tree_black)) {
                    w->color = __rb_tree_red;
                    x = x_parent;
                    x_parent = x_parent->parent;
                }
                else {
                    if (!w->left || w->left->color == __rb_tree_black) {
                        if (w->right)
                            w->right->color = __rb_tree_black;
                        w->color = __rb_tree_red;
                        _rb_tree_rotate_left(w, root);
                        w = x_parent->left;
                    }
                    w->color = x_parent->color;
                    x_parent->color = __rb_tree_black;
                    if (w->left)
                        w->left->color = __rb_tree_black;
                    _rb_tree_rotate_right(x_parent, root);
                    break;
                }
            }
        }
        if(x){
            x->color = __rb_tree_black;
        }
    }
    return y;
}


//以下为三种erase函数的重载
template <typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc>
void rb_tree<Key, Value, KeyofValue, Compare, Alloc>::erase(iterator position){
    link_type p = reinterpret_cast<link_type>(__rb_tree_erase_balance(position.node, header->parent, header->left, header->right));
    destroy(p);
    --node_count;
}


template <typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc>
typename rb_tree<Key, Value, KeyofValue, Compare, Alloc>::size_type rb_tree<Key, Value, KeyofValue, Compare, Alloc>::erase(const key_type& x){
    std::pair<iterator, iterator> p = equal_range(x);
    size_type n = MINISTL::distance(p.first, p.second);
    erase(p.first, p.second);
    return n;
}

template <typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc>
void rb_tree<Key, Value, KeyofValue, Compare, Alloc>::erase(iterator first, iterator last){
    if(first == begin() && last == end()){
        clear();
    }
    else{
        while(first != last){
            erase(first++);
        }
    }
}

//equal_range lower_bound upper_bound
template<typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc>
std::pair<typename rb_tree<Key, Value, KeyofValue, Compare, Alloc>::iterator,typename rb_tree<Key, Value, KeyofValue, Compare, Alloc>::iterator> 
rb_tree<Key, Value, KeyofValue, Compare, Alloc>::equal_range(const key_type& k){
    return std::pair<iterator, iterator> (lower_bound(k), upper_bound(k));
}



template<typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc>
typename rb_tree<Key, Value, KeyofValue, Compare, Alloc>::iterator 
rb_tree<Key, Value, KeyofValue, Compare, Alloc>::lower_bound(const key_type& k){
    link_type y = header;
    link_type x = root();
    while (x)
        if(!key_compare(key(x), k))
            y = x, x = left(x);
        else
            x = right(x);
    return iterator(y);
}

template<typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc>
typename rb_tree<Key, Value, KeyofValue, Compare, Alloc>::iterator 
rb_tree<Key, Value, KeyofValue, Compare, Alloc>::upper_bound(const key_type& k){
    link_type y = header;
    link_type x = root();
    while (x)
        if (key_compare(k, key(x)))
            y = x, x = left(x);
        else
            x = right(x);
    return iterator(y);
}


//operator == , operator <
template<typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc>
bool operator == (const rb_tree<Key, Value, KeyofValue, Compare, Alloc>& lhs, const rb_tree<Key, Value, KeyofValue, Compare, Alloc>& rhs){
    return lhs.size() == rhs.size() && MINISTL::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc>
bool operator != (const rb_tree<Key, Value, KeyofValue, Compare, Alloc>& lhs, const rb_tree<Key, Value, KeyofValue, Compare, Alloc>& rhs){
    return !(lhs == rhs);
}


// template<typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc>
// bool operator < (const rb_tree<Key, Value, KeyofValue, Compare, Alloc>& lhs, const rb_tree<Key, Value, KeyofValue, Compare, Alloc>& rhs){
//     return lhs.size() == rhs.size() && MINISTL::equal(lhs.begin(), lhs.end(), rhs.begin());
// }





}       //namespace MINISTL

#endif //MINISTL_SRC_CONTAINER_ASSOCIATIVE_RBTREE_H
