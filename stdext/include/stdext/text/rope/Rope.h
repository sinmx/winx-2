/* -------------------------------------------------------------------------
// WINX: a C++ template GUI library - MOST SIMPLE BUT EFFECTIVE
// 
// This file is a part of the WINX Library.
// The use and distribution terms for this software are covered by the
// Common Public License 1.0 (http://opensource.org/licenses/cpl.php)
// which can be found in the file CPL.txt at this distribution. By using
// this software in any fashion, you are agreeing to be bound by the terms
// of this license. You must not remove this notice, or any other, from
// this software.
// 
// Module: stdext/text/rope/Rope.h
// Creator: xushiwei
// Email: xushiweizh@gmail.com
// Date: 2006-8-18 18:56:07
// 
// $Id: Rope.h,v 1.1 2006/10/18 12:13:39 xushiwei Exp $
// -----------------------------------------------------------------------*/
#ifndef __STDEXT_TEXT_ROPE_ROPE_H__
#define __STDEXT_TEXT_ROPE_ROPE_H__

#ifndef __SGI_NUMERIC_H__
#include "../../sgi/numeric.h"
#endif

#ifndef __STDEXT_TEXT_ROPE_ROPEREP_H__
#include "RopeRep.h"
#endif

#ifndef __STDEXT_TEXT_ROPE_ROPEITER_H__
#include "RopeIter.h"
#endif

/*
 * Copyright (c) 1997-1998
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

// Rope<_CharT,_Alloc> is a sequence of _CharT.
// Ropes appear to be mutable, but update operations
// really copy enough of the data structure to leave the original
// valid.  Thus ropes can be logically copied by just copying
// a pointer value.

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1174
#endif

__NS_STD_BEGIN

template<class _CharT, class _Alloc> class _Rope_char_ref_proxy;
template<class _CharT, class _Alloc> class _Rope_char_ptr_proxy;
template<class _CharT, class _Alloc> class _Rope_iterator_base;
template<class _CharT, class _Alloc> class _Rope_iterator;
template<class _CharT, class _Alloc> class _Rope_const_iterator;

template <class _CharT, class _Alloc = ScopeAlloc>
class Rope {
    public:
        typedef _CharT value_type;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef _CharT const_reference;
        typedef const _CharT* const_pointer;
        typedef _Rope_iterator<_CharT,_Alloc> iterator;
        typedef _Rope_const_iterator<_CharT,_Alloc> const_iterator;
        typedef _Rope_char_ref_proxy<_CharT,_Alloc> reference;
        typedef _Rope_char_ptr_proxy<_CharT,_Alloc> pointer;

        friend struct _Rope_RopeRep<_CharT>;
        friend struct _Rope_RopeSubstring<_CharT>;

        friend class _Rope_iterator<_CharT,_Alloc>;
        friend class _Rope_const_iterator<_CharT,_Alloc>;
        friend class _Rope_iterator_base<_CharT,_Alloc>;
        friend class _Rope_char_ptr_proxy<_CharT,_Alloc>;
        friend class _Rope_char_ref_proxy<_CharT,_Alloc>;

    protected:
        _Rope_RopeRep<_CharT>* _M_tree_ptr;
		_Alloc* _M_alloc;

        static bool _S_is0(_CharT __c) { return __c == _S_eos((_CharT*)0); }
        enum { _S_copy_max = 23 };
                // For strings shorter than _S_copy_max, we copy to
                // concatenate.

        typedef _Rope_RopeRep<_CharT> _RopeRep;
        typedef _Rope_RopeConcatenation<_CharT> _RopeConcatenation;
        typedef _Rope_RopeLeaf<_CharT> _RopeLeaf;
        typedef _Rope_RopeFunction<_CharT> _RopeFunction;
        typedef _Rope_RopeSubstring<_CharT> _RopeSubstring;

        // Retrieve a character at the indicated position.
        static _CharT _S_fetch(_RopeRep* __r, size_type __pos);

        static bool _S_apply_to_pieces(
                                // should be template parameter
                                _Rope_char_consumer<_CharT>& __c,
                                const _RopeRep* __r,
                                size_t __begin, size_t __end);
                                // begin and end are assumed to be in range.

		typedef _Rope_RopeRep<_CharT>* _Self_destruct_ptr;

        // _Result is counted in refcount.
		static _RopeRep* _S_substring(_RopeRep* __base,
                                    size_t __start, size_t __endp1, _Alloc& __a);

        static _RopeRep* _S_concat_char_iter(_RopeRep* __r,
                                          const _CharT* __iter, size_t __slen, _Alloc& __a);
                // Concatenate Rope and char ptr, copying __s.
                // Should really take an arbitrary iterator.
                // Result is counted in refcount.
        static _RopeRep* _S_destr_concat_char_iter(_RopeRep* __r,
                                          const _CharT* __iter, size_t __slen, _Alloc& __a)
                // As above, but one reference to __r is about to be
                // destroyed.  Thus the pieces may be recycled if all
                // relevent reference counts are 1.
                { return _S_concat_char_iter(__r, __iter, __slen, __a); }

        static _RopeRep* _S_concat(_RopeRep* __left, _RopeRep* __right, _Alloc& __a);
                // General concatenation on _RopeRep.  _Result
                // has refcount of 1.  Adjusts argument refcounts.

   public:
        void apply_to_pieces( size_t __begin, size_t __end,
                              _Rope_char_consumer<_CharT>& __c) const {
            _S_apply_to_pieces(__c, _M_tree_ptr, __begin, __end);
        }


   protected:

        static size_t _S_rounded_up_size(size_t __n) {
            return _RopeLeaf::_S_rounded_up_size(__n);
        }

        static size_t _S_allocated_capacity(size_t __n) {
            if (_S_is_basic_char_type((_CharT*)0)) {
                return _S_rounded_up_size(__n) - 1;
            } else {
                return _S_rounded_up_size(__n);
            }
        }
                
        // Allocate and construct a RopeLeaf using the supplied allocator
        // Takes ownership of s instead of copying.
        static _RopeLeaf* _S_new_RopeLeaf(const _CharT *__s,
                                          size_t __size, _Alloc& __a)
        {
			return STD_NEW(__a, _RopeLeaf)(__s, __size);
        }

        static _RopeConcatenation* _S_new_RopeConcatenation(
                        _RopeRep* __left, _RopeRep* __right,
                        _Alloc& __a)
        {
            return STD_NEW(__a, _RopeConcatenation)(__left, __right);
        }

        static _RopeFunction* _S_new_RopeFunction(CharProducer<_CharT>* __f,
                size_t __size, bool __d, _Alloc& __a)
        {
            return STD_NEW(__a, _RopeFunction)(__f, __size, __d);
        }

        static _RopeSubstring* _S_new_RopeSubstring(
                _Rope_RopeRep<_CharT>* __b, size_t __s,
                size_t __l, _Alloc& __a)
        {
            return STD_NEW(__a, _RopeSubstring)(__b, __s, __l);
        }

#define __STL_ROPE_FROM_UNOWNED_CHAR_PTR(__s, __size, __a)	\
	_S_RopeLeaf_from_unowned_char_ptr(__s, __size, __a)     

		static _RopeLeaf* _S_RopeLeaf_from_unowned_char_ptr(const _CharT *__s,
                       size_t __size, _Alloc& __a)
        {
            if (0 == __size) return 0;
            _CharT* __buf = STD_ALLOC_ARRAY(__a, _CharT, _S_rounded_up_size(__size));
            uninitialized_copy_n(__s, __size, __buf);
            return _S_new_RopeLeaf(__buf, __size, __a);
        }
            

        // Concatenation of nonempty strings.
        // Always builds a concatenation node.
        // Rebalances if the result is too deep.
        // Result has refcount 1.
        // Does not increment left and right ref counts even though
        // they are referenced.
        static _RopeRep*
        _S_tree_concat(_RopeRep* __left, _RopeRep* __right);

        // Concatenation helper functions
        static _RopeLeaf*
        _S_leaf_concat_char_iter(_RopeLeaf* __r,
                                 const _CharT* __iter, size_t __slen, _Alloc& __a);
                // Concatenate by copying leaf.
                // should take an arbitrary iterator
                // result has refcount 1.

        private:

        static size_t _S_char_ptr_len(const _CharT* __s);
                        // slightly generalized strlen

        Rope(_Alloc& __a, _RopeRep* __t)
          : _M_alloc(&__a), _M_tree_ptr(__t) {}


        // Copy __r to the _CharT buffer.
        // Returns __buffer + __r->_M_size.
        // Assumes that buffer is uninitialized.
        static _CharT* _S_flatten(_RopeRep* __r, _CharT* __buffer);

        // Again, with explicit starting position and length.
        // Assumes that buffer is uninitialized.
        static _CharT* _S_flatten(_RopeRep* __r,
                                  size_t __start, size_t __len,
                                  _CharT* __buffer);

        static const unsigned long 
          _S_min_len[_RopeRep::_S_max_rope_depth + 1];

        static bool _S_is_balanced(_RopeRep* __r)
                { return (__r->_M_size >= _S_min_len[__r->_M_depth]); }

        static bool _S_is_almost_balanced(_RopeRep* __r)
                { return (__r->_M_depth == 0 ||
                          __r->_M_size >= _S_min_len[__r->_M_depth - 1]); }

        static bool _S_is_roughly_balanced(_RopeRep* __r)
                { return (__r->_M_depth <= 1 ||
                          __r->_M_size >= _S_min_len[__r->_M_depth - 2]); }

        // Assumes the result is not empty.
        static _RopeRep* _S_concat_and_set_balanced(_RopeRep* __left,
                                                     _RopeRep* __right, _Alloc& __a)
        {
            _RopeRep* __result = _S_concat(__left, __right, __a);
            if (_S_is_balanced(__result)) __result->_M_is_balanced = true;
            return __result;
        }

        // The basic rebalancing operation.  Logically copies the
        // Rope.  The result has refcount of 1.  The client will
        // usually decrement the reference count of __r.
        // The result is within height 2 of balanced by the above
        // definition.
        static _RopeRep* _S_balance(_RopeRep* __r, _Alloc& __a);

        // Add all unbalanced subtrees to the forest of balanceed trees.
        // Used only by balance.
        static void _S_add_to_forest(_RopeRep*__r, _RopeRep** __forest);
        
        // Add __r to forest, assuming __r is already balanced.
        static void _S_add_leaf_to_forest(_RopeRep* __r, _RopeRep** __forest);

        // Print to stdout, exposing structure
        static void _S_dump(_RopeRep* __r, int __indent = 0);

        // Return -1, 0, or 1 if __x < __y, __x == __y, or __x > __y resp.
        static int _S_compare(const _RopeRep* __x, const _RopeRep* __y);

   public:
        bool empty() const { return 0 == _M_tree_ptr; }

        // Comparison member function.  This is public only for those
        // clients that need a ternary comparison.  Others
        // should use the comparison operators below.
        int compare(const Rope& __y) const {
            return _S_compare(_M_tree_ptr, __y._M_tree_ptr);
        }

        Rope(_Alloc& __a, const _CharT* __s)
        : _M_alloc(&__a),
		  _M_tree_ptr(__STL_ROPE_FROM_UNOWNED_CHAR_PTR(__s, _S_char_ptr_len(__s), __a))
        { }

        Rope(_Alloc& __a, const _CharT* __s, size_t __len)
        : _M_alloc(&__a), 
		  _M_tree_ptr(__STL_ROPE_FROM_UNOWNED_CHAR_PTR(__s, __len, __a))
        { }

        // Should perhaps be templatized with respect to the iterator type
        // and use Sequence_buffer.  (It should perhaps use sequence_buffer
        // even now.)
        Rope(_Alloc& __a, const _CharT *__s, const _CharT *__e)
        : _M_alloc(&__a),
		  _M_tree_ptr(__STL_ROPE_FROM_UNOWNED_CHAR_PTR(__s, __e - __s, __a))
        { }

        Rope(_Alloc& __a, const const_iterator& __s, const const_iterator& __e)
        : _M_alloc(&__a),
		  _M_tree_ptr(_S_substring(__s._M_root, __s._M_current_pos,
                             __e._M_current_pos))
        { }

        Rope(_Alloc& __a, const iterator& __s, const iterator& __e)
        : _M_alloc(&__a),
		  _M_tree_ptr(_S_substring(__s._M_root, __s._M_current_pos,
                             __e._M_current_pos))
        { }

        Rope(_Alloc& __a, _CharT __c)
        : _M_alloc(&__a)
        {
            _CharT* __buf = STD_ALLOC_ARRAY(__a, _CharT, _S_rounded_up_size(1));
            construct(__buf, __c);
			_M_tree_ptr = _S_new_RopeLeaf(__buf, 1, __a);
        }

        Rope(_Alloc& __a, size_t __n, _CharT __c);

        Rope(_Alloc& __a)
		: _M_alloc(&__a), _M_tree_ptr(0) {}

        // Construct a Rope from a function that can compute its members
        Rope(_Alloc& __a, CharProducer<_CharT> *__fn, size_t __len, bool __delete_fn)
            : _M_alloc(&__a)
        {
            _M_tree_ptr = (0 == __len) ?
               0 : _S_new_RopeFunction(__fn, __len, __delete_fn, __a);
        }

        void clear()
        {
            _M_tree_ptr = 0;
        }

        void push_back(_CharT __x)
        {
            _RopeRep* __old = _M_tree_ptr;
            _M_tree_ptr = _S_destr_concat_char_iter(_M_tree_ptr, &__x, 1);
        }

        void pop_back()
        {
            _RopeRep* __old = _M_tree_ptr;
            _M_tree_ptr = 
              _S_substring(_M_tree_ptr, 0, _M_tree_ptr->_M_size - 1);
        }

        _CharT back() const
        {
            return _S_fetch(_M_tree_ptr, _M_tree_ptr->_M_size - 1);
        }

        void push_front(_CharT __x)
        {
            _RopeRep* __old = _M_tree_ptr;
            _RopeRep* __left =
				__STL_ROPE_FROM_UNOWNED_CHAR_PTR(&__x, 1, get_allocator());
			_M_tree_ptr = _S_concat(__left, _M_tree_ptr, *_M_alloc);
        }

        void pop_front()
        {
            _RopeRep* __old = _M_tree_ptr;
            _M_tree_ptr = _S_substring(_M_tree_ptr, 1, _M_tree_ptr->_M_size);
        }

        _CharT front() const
        {
            return _S_fetch(_M_tree_ptr, 0);
        }

        void balance()
        {
            _RopeRep* __old = _M_tree_ptr;
            _M_tree_ptr = _S_balance(_M_tree_ptr);
        }

		void copy(Rope& __r) {
			*this = __r;
		}

        void copy(_CharT* __buffer) const {
            destroy(__buffer, __buffer + size());
            _S_flatten(_M_tree_ptr, __buffer);
        }

        // This is the copy function from the standard, but
        // with the arguments reordered to make it consistent with the
        // rest of the interface.
        // Note that this guaranteed not to compile if the draft standard
        // order is assumed.
        size_type copy(size_type __pos, size_type __n, _CharT* __buffer) const 
        {
            size_t __size = size();
            size_t __len = (__pos + __n > __size? __size - __pos : __n);

            destroy(__buffer, __buffer + __len);
            _S_flatten(_M_tree_ptr, __pos, __len, __buffer);
            return __len;
        }

        // Print to stdout, exposing structure.  May be useful for
        // performance debugging.
        void dump() {
            _S_dump(_M_tree_ptr);
        }

        _CharT operator[] (size_type __pos) const {
            return _S_fetch(_M_tree_ptr, __pos);
        }

        _CharT at(size_type __pos) const {
           // if (__pos >= size()) throw out_of_range;  // XXX
           return (*this)[__pos];
        }

        const_iterator begin() const {
            return(const_iterator(_M_tree_ptr, 0));
        }

        // An easy way to get a const iterator from a non-const container.
        const_iterator const_begin() const {
            return(const_iterator(_M_tree_ptr, 0));
        }

        const_iterator end() const {
            return(const_iterator(_M_tree_ptr, size()));
        }

        const_iterator const_end() const {
            return(const_iterator(_M_tree_ptr, size()));
        }

        size_type size() const { 
            return(0 == _M_tree_ptr? 0 : _M_tree_ptr->_M_size);
        }

        size_type length() const {
            return size();
        }

        size_type max_size() const {
            return _S_min_len[_RopeRep::_S_max_rope_depth-1] - 1;
            //  Guarantees that the result can be sufficirntly
            //  balanced.  Longer ropes will probably still work,
            //  but it's harder to make guarantees.
        }

#     if defined(__STL_CLASS_PARTIAL_SPECIALIZATION) || defined(X_CC_VC_NET)
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
#     else /* __STL_CLASS_PARTIAL_SPECIALIZATION */
        typedef reverse_iterator<const_iterator, value_type, const_reference,
                                 difference_type>  const_reverse_iterator;
#     endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */ 

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }

        const_reverse_iterator const_rbegin() const {
            return const_reverse_iterator(end());
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }

        const_reverse_iterator const_rend() const {
            return const_reverse_iterator(begin());
        }

#if defined(__STL_MEMBER_TEMPLATES) && defined(__STL_FUNCTION_TMPL_PARTIAL_ORDER)
        template<class _CharT2, class _Alloc2>
        friend Rope<_CharT2,_Alloc2>
        operator+ (const Rope<_CharT2,_Alloc2>& __left,
                   const Rope<_CharT2,_Alloc2>& __right);
        
        template<class _CharT2, class _Alloc2>
        friend Rope<_CharT2,_Alloc2>
        operator+ (const Rope<_CharT2,_Alloc2>& __left,
                   const _CharT2* __right);
        
        template<class _CharT2, class _Alloc2>
        friend Rope<_CharT2,_Alloc2>
        operator+ (const Rope<_CharT2,_Alloc2>& __left, _CharT2 __right);
#else
        friend Rope<_CharT,_Alloc> __STD_QUALIFIER
        operator+ __STL_NULL_TMPL_ARGS (const Rope<_CharT,_Alloc>& __left,
                                        const Rope<_CharT,_Alloc>& __right);
        
        friend Rope<_CharT,_Alloc> __STD_QUALIFIER
        operator+ __STL_NULL_TMPL_ARGS (const Rope<_CharT,_Alloc>& __left,
                                        const _CharT* __right);
        
        friend Rope<_CharT,_Alloc> __STD_QUALIFIER
        operator+ __STL_NULL_TMPL_ARGS (const Rope<_CharT,_Alloc>& __left,
                                        _CharT __right);
#endif        
        // The symmetric cases are intentionally omitted, since they're presumed
        // to be less common, and we don't handle them as well.

        // The following should really be templatized.
        // The first argument should be an input iterator or
        // forward iterator with value_type _CharT.
        Rope& append(const _CharT* __iter, size_t __n) {
            _RopeRep* __result = 
              _S_destr_concat_char_iter(_M_tree_ptr, __iter, __n, *_M_alloc);
            _M_tree_ptr = __result;
            return *this;
        }

        Rope& append(const _CharT* __c_string) {
            size_t __len = _S_char_ptr_len(__c_string);
            append(__c_string, __len);
            return(*this);
        }

        Rope& append(const _CharT* __s, const _CharT* __e) {
            _RopeRep* __result =
                _S_destr_concat_char_iter(_M_tree_ptr, __s, __e - __s, *_M_alloc);
            _M_tree_ptr = __result;
            return *this;
        }

        Rope& append(const_iterator __s, const_iterator __e) {
            __stl_assert(__s._M_root == __e._M_root);
            _Self_destruct_ptr __appendee(_S_substring(
              __s._M_root, __s._M_current_pos, __e._M_current_pos));
            _RopeRep* __result = 
              _S_concat(_M_tree_ptr, (_RopeRep*)__appendee, *_M_alloc);
            _M_tree_ptr = __result;
            return *this;
        }

        Rope& append(_CharT __c) {
            _RopeRep* __result = 
              _S_destr_concat_char_iter(_M_tree_ptr, &__c, 1);
            _M_tree_ptr = __result;
            return *this;
        }

        Rope& append(const Rope& __y) {
            _RopeRep* __result = _S_concat(_M_tree_ptr, __y._M_tree_ptr, *_M_alloc);
            _M_tree_ptr = __result;
            return *this;
        }

        Rope& append(size_t __n, _CharT __c) {
            Rope<_CharT,_Alloc> __last(*_M_alloc, __n, __c);
            return append(__last);
        }

        void swap(Rope& __b) {
			std::swap(_M_alloc, __b._M_alloc);
			std::swap(_M_tree_ptr, __b._M_tree_ptr);
        }

    protected:
        // Result is included in refcount.
        static _RopeRep* replace(_RopeRep* __old, size_t __pos1,
                                  size_t __pos2, _RopeRep* __r, _Alloc& __a) {
            if (0 == __old) { return __r; }
            _Self_destruct_ptr __left(
              _S_substring(__old, 0, __pos1, __a));
            _Self_destruct_ptr __right(
              _S_substring(__old, __pos2, __old->_M_size, __a));
            _RopeRep* __result;

            if (0 == __r) {
                __result = _S_concat(__left, __right, __a);
            } else {
                _Self_destruct_ptr __left_result(_S_concat(__left, __r, __a));
                __result = _S_concat(__left_result, __right, __a);
            }
            return __result;
        }

    public:
        void insert(size_t __p, const Rope& __r) {
            _RopeRep* __result = 
				replace(_M_tree_ptr, __p, __p, __r._M_tree_ptr);
            _M_tree_ptr = __result;
        }

        void insert(size_t __p, size_t __n, _CharT __c) {
            Rope<_CharT,_Alloc> __r(__n,__c);
            insert(__p, __r);
        }

        void insert(size_t __p, const _CharT* __i, size_t __n) {
            _Self_destruct_ptr __left(_S_substring(_M_tree_ptr, 0, __p));
            _Self_destruct_ptr __right(_S_substring(_M_tree_ptr, __p, size()));
            _Self_destruct_ptr __left_result(
              _S_concat_char_iter(__left, __i, __n));
                // _S_ destr_concat_char_iter should be safe here.
                // But as it stands it's probably not a win, since __left
                // is likely to have additional references.
            _RopeRep* __result = _S_concat(__left_result, __right, *_M_alloc);
            _M_tree_ptr = __result;
        }

        void insert(size_t __p, const _CharT* __c_string) {
            insert(__p, __c_string, _S_char_ptr_len(__c_string));
        }

        void insert(size_t __p, _CharT __c) {
            insert(__p, &__c, 1);
        }

        void insert(size_t __p) {
            _CharT __c = _CharT();
            insert(__p, &__c, 1);
        }

        void insert(size_t __p, const _CharT* __i, const _CharT* __j) {
            Rope __r(__i, __j);
            insert(__p, __r);
        }

        void insert(size_t __p, const const_iterator& __i,
                              const const_iterator& __j) {
            Rope __r(__i, __j);
            insert(__p, __r);
        }

        void insert(size_t __p, const iterator& __i,
                              const iterator& __j) {
            Rope __r(__i, __j);
            insert(__p, __r);
        }

        // (position, length) versions of replace operations:

        void replace(size_t __p, size_t __n, const Rope& __r) {
            _RopeRep* __result = 
              replace(_M_tree_ptr, __p, __p + __n, __r._M_tree_ptr);
            _M_tree_ptr = __result;
        }

        void replace(size_t __p, size_t __n, 
                     const _CharT* __i, size_t __i_len) {
            Rope __r(__i, __i_len);
            replace(__p, __n, __r);
        }

        void replace(size_t __p, size_t __n, _CharT __c) {
            Rope __r(__c);
            replace(__p, __n, __r);
        }

        void replace(size_t __p, size_t __n, const _CharT* __c_string) {
            Rope __r(__c_string);
            replace(__p, __n, __r);
        }

        void replace(size_t __p, size_t __n, 
                     const _CharT* __i, const _CharT* __j) {
            Rope __r(__i, __j);
            replace(__p, __n, __r);
        }

        void replace(size_t __p, size_t __n,
                     const const_iterator& __i, const const_iterator& __j) {
            Rope __r(__i, __j);
            replace(__p, __n, __r);
        }

        void replace(size_t __p, size_t __n,
                     const iterator& __i, const iterator& __j) {
            Rope __r(__i, __j);
            replace(__p, __n, __r);
        }

        // Single character variants:
        void replace(size_t __p, _CharT __c) {
            iterator __i(this, __p);
            *__i = __c;
        }

        void replace(size_t __p, const Rope& __r) {
            replace(__p, 1, __r);
        }

        void replace(size_t __p, const _CharT* __i, size_t __i_len) {
            replace(__p, 1, __i, __i_len);
        }

        void replace(size_t __p, const _CharT* __c_string) {
            replace(__p, 1, __c_string);
        }

        void replace(size_t __p, const _CharT* __i, const _CharT* __j) {
            replace(__p, 1, __i, __j);
        }

        void replace(size_t __p, const const_iterator& __i,
                               const const_iterator& __j) {
            replace(__p, 1, __i, __j);
        }

        void replace(size_t __p, const iterator& __i,
                               const iterator& __j) {
            replace(__p, 1, __i, __j);
        }

        // Erase, (position, size) variant.
        void erase(size_t __p, size_t __n) {
            _RopeRep* __result = replace(_M_tree_ptr, __p, __p + __n, 0, *_M_alloc);
            _M_tree_ptr = __result;
        }

        // Erase, single character
        void erase(size_t __p) {
            erase(__p, __p + 1);
        }

        // Insert, iterator variants.  
        iterator insert(const iterator& __p, const Rope& __r)
                { insert(__p.index(), __r); return __p; }
        iterator insert(const iterator& __p, size_t __n, _CharT __c)
                { insert(__p.index(), __n, __c); return __p; }
        iterator insert(const iterator& __p, _CharT __c) 
                { insert(__p.index(), __c); return __p; }
        iterator insert(const iterator& __p ) 
                { insert(__p.index()); return __p; }
        iterator insert(const iterator& __p, const _CharT* c_string) 
                { insert(__p.index(), c_string); return __p; }
        iterator insert(const iterator& __p, const _CharT* __i, size_t __n)
                { insert(__p.index(), __i, __n); return __p; }
        iterator insert(const iterator& __p, const _CharT* __i, 
                        const _CharT* __j)
                { insert(__p.index(), __i, __j);  return __p; }
        iterator insert(const iterator& __p,
                        const const_iterator& __i, const const_iterator& __j)
                { insert(__p.index(), __i, __j); return __p; }
        iterator insert(const iterator& __p,
                        const iterator& __i, const iterator& __j)
                { insert(__p.index(), __i, __j); return __p; }

        // Replace, range variants.
        void replace(const iterator& __p, const iterator& __q,
                     const Rope& __r)
                { replace(__p.index(), __q.index() - __p.index(), __r); }
        void replace(const iterator& __p, const iterator& __q, _CharT __c)
                { replace(__p.index(), __q.index() - __p.index(), __c); }
        void replace(const iterator& __p, const iterator& __q,
                     const _CharT* __c_string)
                { replace(__p.index(), __q.index() - __p.index(), __c_string); }
        void replace(const iterator& __p, const iterator& __q,
                     const _CharT* __i, size_t __n)
                { replace(__p.index(), __q.index() - __p.index(), __i, __n); }
        void replace(const iterator& __p, const iterator& __q,
                     const _CharT* __i, const _CharT* __j)
                { replace(__p.index(), __q.index() - __p.index(), __i, __j); }
        void replace(const iterator& __p, const iterator& __q,
                     const const_iterator& __i, const const_iterator& __j)
                { replace(__p.index(), __q.index() - __p.index(), __i, __j); }
        void replace(const iterator& __p, const iterator& __q,
                     const iterator& __i, const iterator& __j)
                { replace(__p.index(), __q.index() - __p.index(), __i, __j); }

        // Replace, iterator variants.
        void replace(const iterator& __p, const Rope& __r)
                { replace(__p.index(), __r); }
        void replace(const iterator& __p, _CharT __c)
                { replace(__p.index(), __c); }
        void replace(const iterator& __p, const _CharT* __c_string)
                { replace(__p.index(), __c_string); }
        void replace(const iterator& __p, const _CharT* __i, size_t __n)
                { replace(__p.index(), __i, __n); }
        void replace(const iterator& __p, const _CharT* __i, const _CharT* __j)
                { replace(__p.index(), __i, __j); }
        void replace(const iterator& __p, const_iterator __i, 
                     const_iterator __j)
                { replace(__p.index(), __i, __j); }
        void replace(const iterator& __p, iterator __i, iterator __j)
                { replace(__p.index(), __i, __j); }

        // Iterator and range variants of erase
        iterator erase(const iterator& __p, const iterator& __q) {
            size_t __p_index = __p.index();
            erase(__p_index, __q.index() - __p_index);
            return iterator(this, __p_index);
        }
        iterator erase(const iterator& __p) {
            size_t __p_index = __p.index();
            erase(__p_index, 1);
            return iterator(this, __p_index);
        }

        Rope substr(size_t __start, size_t __len = 1) const {
            return Rope<_CharT,_Alloc>(
                        _S_substring(_M_tree_ptr, __start, __start + __len));
        }

        Rope substr(iterator __start, iterator __end) const {
            return Rope<_CharT,_Alloc>(
                _S_substring(_M_tree_ptr, __start.index(), __end.index()));
        }
        
        Rope substr(iterator __start) const {
            size_t __pos = __start.index();
            return Rope<_CharT,_Alloc>(
                        _S_substring(_M_tree_ptr, __pos, __pos + 1));
        }
        
        Rope substr(const_iterator __start, const_iterator __end) const {
            // This might eventually take advantage of the cache in the
            // iterator.
            return Rope<_CharT,_Alloc>(
              _S_substring(_M_tree_ptr, __start.index(), __end.index()));
        }

        Rope<_CharT,_Alloc> substr(const_iterator __start) {
            size_t __pos = __start.index();
            return Rope<_CharT,_Alloc>(
              _S_substring(_M_tree_ptr, __pos, __pos + 1));
        }

        static const size_type npos;

        size_type find(_CharT __c, size_type __pos = 0) const;
        size_type find(const _CharT* __s, size_type __pos = 0) const {
            size_type __result_pos;
            const_iterator __result = search(const_begin() + __pos, const_end(),
                                           __s, __s + _S_char_ptr_len(__s));
            __result_pos = __result.index();
#           ifndef __STL_OLD_ROPE_SEMANTICS
                if (__result_pos == size()) __result_pos = npos;
#           endif
            return __result_pos;
        }

        iterator mutable_begin() {
            return(iterator(this, 0));
        }

        iterator mutable_end() {
            return(iterator(this, size()));
        }

#     if defined(__STL_CLASS_PARTIAL_SPECIALIZATION) || defined(X_CC_VC_NET)
        typedef reverse_iterator<iterator> reverse_iterator;
#     else /* __STL_CLASS_PARTIAL_SPECIALIZATION */
        typedef reverse_iterator<iterator, value_type, reference,
                                 difference_type>  reverse_iterator;
#     endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */ 

        reverse_iterator mutable_rbegin() {
            return reverse_iterator(mutable_end());
        }

        reverse_iterator mutable_rend() {
            return reverse_iterator(mutable_begin());
        }

        reference mutable_reference_at(size_type __pos) {
            return reference(this, __pos);
        }

#       ifdef __STD_STUFF
            reference operator[] (size_type __pos) {
                return _char_ref_proxy(this, __pos);
            }

            reference at(size_type __pos) {
                // if (__pos >= size()) throw out_of_range;  // XXX
                return (*this)[__pos];
            }

            void resize(size_type __n, _CharT __c) {}
            void resize(size_type __n) {}
            void reserve(size_type __res_arg = 0) {}
            size_type capacity() const {
                return max_size();
            }

          // Stuff below this line is dangerous because it's error prone.
          // I would really like to get rid of it.
            // copy function with funny arg ordering.
              size_type copy(_CharT* __buffer, size_type __n, 
                             size_type __pos = 0) const {
                return copy(__pos, __n, __buffer);
              }

            iterator end() { return mutable_end(); }

            iterator begin() { return mutable_begin(); }

            reverse_iterator rend() { return mutable_rend(); }

            reverse_iterator rbegin() { return mutable_rbegin(); }

#       else

            const_iterator end() { return const_end(); }

            const_iterator begin() { return const_begin(); }

            const_reverse_iterator rend() { return const_rend(); }
  
            const_reverse_iterator rbegin() { return const_rbegin(); }

#       endif
        
};

template <class _CharT, class _Alloc>
const typename Rope<_CharT, _Alloc>::size_type Rope<_CharT, _Alloc>::npos =
                        (size_type)(-1);

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma reset woff 1174
#endif

__NS_STD_END

#include "RopeImpl.h"

// -------------------------------------------------------------------------
// $Log: Rope.h,v $

#endif /* __STDEXT_TEXT_ROPE_ROPE_H__ */
