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
// Module: stdext/archive/Reader.h
// Creator: xushiwei
// Email: xushiweizh@gmail.com
// Date: 2006-11-29 19:27:08
// 
// $Id: Reader.h,v 1.4 2006/12/14 09:15:04 xushiwei Exp $
// -----------------------------------------------------------------------*/
#ifndef __STDEXT_ARCHIVE_READER_H__
#define __STDEXT_ARCHIVE_READER_H__

#ifndef __STDEXT_ARCHIVE_BASIC_H__
#include "Basic.h"
#endif

#ifndef __STDEXT_TEXT_BASICSTRING_H__
#include "../text/BasicString.h"
#endif

__NS_STD_BEGIN

// -------------------------------------------------------------------------
// class Reader

template <class BaseArchive>
class Reader : public BaseArchive
{
private:
	typedef BaseArchive _Base, BaseClass;
	typedef Reader _Myt;

public:
	typedef size_t size_type;
	typedef char char_type;
	typedef unsigned char uchar_type;
	typedef UINT16 word_type;
	typedef UINT32 dword_type;
	typedef int int_type;
	typedef unsigned uint_type;

public:
	template <class AllocT>
	explicit Reader(AllocT& alloc)
		: _Base(alloc) {}

	template <class AllocT, class InitArgT>
	Reader(AllocT& alloc, InitArgT file)
		: _Base(alloc, file) {}

	template <class AllocT, class InitArgT1, class InitArgT2>
	Reader(AllocT& alloc, InitArgT1 arg1, InitArgT2 arg2)
		: _Base(alloc, arg1, arg2) {}

//
// ======== access binary data ========
//
public:
	// get a binary string

	template <class AllocT>
	HRESULT winx_call gets(AllocT& alloc, BasicString<char_type>& s)
	{
		OutputBasicString<char_type, AllocT> s1(alloc, s);
		return gets(s1);
	}

	template <class StringT>
	HRESULT winx_call gets(StringT& s)
	{
		HRESULT hr;
		uint_type cch = _Base::get();
		if (cch < 254) {
			/* nothing todo */
		}
		else if (cch == 254) {
			UINT16 cch2;
			hr = get16i(cch2);
			if (hr != S_OK)
				return hr;
			cch = cch2;
		}
		else if (cch == 255) {
			INT32 cch4;
			hr = get32i(cch4);
			if (hr != S_OK && cch4 < 0)
				return STG_E_READFAULT;
			cch = cch4;
		}
		else {
			return E_UNEXPECTED;
		}
		UINT cbRead = get(std::resize(s, cch), cch);
		if (cbRead != cch)
			return STG_E_READFAULT;
		if ( !(cch & 1) )
			_Base::get(); // padding
		return S_OK;
	}

public:
	// get binary data
	
	size_type winx_call read(void* lpBuf, size_type nMax)
	{
		return get( (char*)lpBuf, nMax );
	}

	HRESULT winx_call get16i(UINT16& val)
	{
		UINT cbRead = get( (char*)&val, sizeof(val) );
		if (cbRead != sizeof(val))
			return STG_E_READFAULT;

		_WinxByteSwap16(val);
		return S_OK;
	}
	
	HRESULT winx_call get16i(INT16& val)
	{
		UINT cbRead = get( (char*)&val, sizeof(val) );
		if (cbRead != sizeof(val))
			return STG_E_READFAULT;
		
		_WinxByteSwap16(val);
		return S_OK;
	}

	HRESULT winx_call get32i(UINT32& val)
	{
		UINT cbRead = get( (char*)&val, sizeof(val) );
		if (cbRead != sizeof(val))
			return STG_E_READFAULT;
		
		_WinxByteSwap32(val);
		return S_OK;
	}

	HRESULT winx_call get32i(INT32& val)
	{
		UINT cbRead = get( (char*)&val, sizeof(val) );
		if (cbRead != sizeof(val))
			return STG_E_READFAULT;
		
		_WinxByteSwap32(val);
		return S_OK;
	}
	
	template <class StrucType>
	HRESULT winx_call get_struct(StrucType& val)
	{
		UINT cbRead = get( (char*)&val, sizeof(val) );
		if (cbRead != sizeof(val))
			return STG_E_READFAULT;
		
		_WinxByteSwapStruct(val);
		return S_OK;
	}

#if defined(WINX_BYTESWAP)
	HRESULT winx_call get16i(IN UINT16 warray[], IN UINT count)
	{
		HRESULT hr = S_OK;
		for (UINT i = 0; i < count; ++i)
			hr = get16u(warray[i]);
		return hr;
	}
	HRESULT winx_call get16i(IN INT16 warray[], IN UINT count)
	{
		HRESULT hr = S_OK;
		for (UINT i = 0; i < count; ++i)
			hr = get16i(warray[i]);
		return hr;
	}
	HRESULT winx_call get32i(IN UINT32 dwarray[], IN UINT count)
	{
		HRESULT hr = S_OK;
		for (UINT i = 0; i < count; ++i)
			hr = get32u(warray[i]);
		return hr;
	}
	HRESULT winx_call get32i(IN INT32 dwarray[], IN UINT count)
	{
		HRESULT hr = S_OK;
		for (UINT i = 0; i < count; ++i)
			hr = get32i(warray[i]);
		return hr;
	}
	template <class StrucType>
	HRESULT winx_call get_struct(StrucType* array, UINT count)
	{
		HRESULT hr = S_OK;
		for (UINT i = 0; i < count; ++i)
			hr = get_struct(warray[i]);
		return hr;
	}
#else
	HRESULT winx_call get16i(IN UINT16 warray[], IN UINT count)
	{
		UINT cbToRead = sizeof(UINT16) * count;
		UINT cbRead = get( (char*)warray, cbToRead );
		if (cbRead != cbToRead)
			return STG_E_READFAULT;
		return S_OK;
	}
	HRESULT winx_call get16i(IN INT16 warray[], IN UINT count)
	{
		UINT cbToRead = sizeof(INT16) * count;
		UINT cbRead = get( (char*)warray, cbToRead );
		if (cbRead != cbToRead)
			return STG_E_READFAULT;
		return S_OK;
	}
	HRESULT get32i(IN UINT32 dwarray[], IN UINT count)
	{
		UINT cbToRead = sizeof(UINT32) * count;
		UINT cbRead = get( (char*)dwarray, cbToRead );
		if (cbRead != cbToRead)
			return STG_E_READFAULT;
		return S_OK;
	}
	HRESULT get32i(IN INT32 dwarray[], IN UINT count)
	{
		UINT cbToRead = sizeof(INT32) * count;
		UINT cbRead = get( (char*)dwarray, cbToRead );
		if (cbRead != cbToRead)
			return STG_E_READFAULT;
		return S_OK;
	}
	template <class StrucType>
	HRESULT get_struct(StrucType* array, UINT count)
	{
		UINT cbToRead = sizeof(StrucType) * count;
		UINT cbRead = get( (char*)array, cbToRead );
		if (cbRead != cbToRead)
			return STG_E_READFAULT;
		return S_OK;
	}
#endif // !defined(WINX_BYTESWAP)

//
// ======== access text data ========
//
public:
	template <class ConditionT>
	int_type winx_call get_first_not_of(ConditionT cond)
		{return std::get_first_not_of(WINX_BASE, cond); }

	int_type winx_call getnws()
		{return std::get_nws(WINX_BASE); }

	size_type winx_call skip_eol()
		{return std::skip_eol(WINX_BASE); }

	template <class ConditionT>
	size_type winx_call skip_while(ConditionT cond)
		{return std::skip_while(WINX_BASE, cond); }

	void winx_call skipws()
		{std::skip_ws(WINX_BASE); }

	unsigned winx_call get_uint(unsigned preval = 0, unsigned radix = 10)
		{return std::get_uint(WINX_BASE, preval, radix); }

	HRESULT winx_call scan_uint(unsigned& val, unsigned radix = 10)
		{return std::scan_uint(WINX_BASE, val, radix); }

	template <class StringT, class ConditionT>
	size_type winx_call get_while(StringT& s, ConditionT cond)
		{return std::get_while(WINX_BASE, s, cond); }

	template <class AllocT, class ConditionT>
	size_type winx_call get_while(
		AllocT& alloc, BasicString<char_type>& s, ConditionT cond)
	{
		OutputBasicString<char_type, AllocT> s1(alloc, s);
		return std::get_while(WINX_BASE, s1, cond);
	}

	template <class StringT>
	size_type winx_call getline(StringT& s)
		{return std::get_line(WINX_BASE, s); }

	template <class AllocT>
	size_type winx_call getline(AllocT& alloc, BasicString<char_type>& s)
	{
		OutputBasicString<char_type, AllocT> s1(alloc, s);
		return std::get_line(WINX_BASE, s1);
	}
};

// -------------------------------------------------------------------------
// $Log: Reader.h,v $

__NS_STD_END

#endif /* __STDEXT_ARCHIVE_READER_H__ */