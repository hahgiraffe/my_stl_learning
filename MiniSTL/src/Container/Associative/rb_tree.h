/*
 * @Author: haha_giraffe
 * @Date: 2019-12-03 15:07:55
 * @Description: 红黑树的实现
 */
#ifndef MINISTL_SRC_CONTAINER_ASSOCIATIVE_RBTREE_H
#define MINISTL_SRC_CONTAINER_ASSOCIATIVE_RBTREE_H
#include "../../Iterator/stl_iterator.h"
#include "../../Allocator/allocator.h"
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
    typedef ptrdiff_t didfference_type;

    typedef __rb_tree_iterator<value_type, reference, pointer> iterator;

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
        link_type tmp = create_node(x);
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
    // link_type __copy(link_type x, link_type p);
    // void __erase(link_type x);
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
    // rb_tree<Key, Value, KeyofValue, Compare, Alloc>& operator = (const rb_tree<Key, Value, KeyofValue, Compare, Alloc>& x);

    Compare key_comp() const { return key_compare; }
    iterator begin() { return leftmost(); }
    iterator end() { return header; }
    bool empty() const {return node_count == 0; }
    size_type size() const { return node_count; }
    size_type max_size() const { return size_type(-1); }

    std::pair<iterator, bool> insert_unique(const value_type& x);
    iterator insert_equal(const value_type& x);
    iterator find(const Key& x);

    //还没有实现
    void clear(){

    }
};

// __erase() __copy() operator=() 

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

template <typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc>
typename rb_tree<Key, Value, KeyofValue, Compare, Alloc>::iterator 
rb_tree<Key, Value, KeyofValue, Compare, Alloc>::find(const Key& x){
    
}



}       //namespace MINISTL

#endif //MINISTL_SRC_CONTAINER_ASSOCIATIVE_RBTREE_H