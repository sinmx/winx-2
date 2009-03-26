//*********************************************************************
//*                  Microsoft Windows                               **
//*            Copyright(c) Microsoft Corp., 1996-1997               **
//*********************************************************************

//;begin_internal
/***********************************************************************************************

  This is a distributed SDK component - do not put any #includes or other directives that rely
  upon files not dropped. If in doubt - build iedev

  If you add comments please include either ;BUGBUG at the beginning of a single line OR
  enclose in a ;begin_internal, ;end_internal block - such as this one!

 ***********************************************************************************************/
//;end_internal

//;begin_internal
#ifndef __DOMDID_H__
#define __DOMDID_H__
//;end_internal

//#define DISPID_DOM_BASE                 0x80010500

// Our dispids need to be mapped into the range 1..9999 to kep Trident happy
// specifically, to make the XML tag more efficient. (simonb, 09-18-1998)
#define DISPID_DOM_BASE                 0x00000001

#define DISPID_DOM_NODE                        (DISPID_DOM_BASE)
#define DISPID_DOM_NODE_NODENAME               (DISPID_DOM_NODE + 1)
#define DISPID_DOM_NODE_NODEVALUE              (DISPID_DOM_NODE + 2)
#define DISPID_DOM_NODE_NODETYPE               (DISPID_DOM_NODE + 3)
#define DISPID_DOM_NODE_NODETYPEENUM           (DISPID_DOM_NODE + 4)
#define DISPID_DOM_NODE_PARENTNODE             (DISPID_DOM_NODE + 5)
#define DISPID_DOM_NODE_CHILDNODES             (DISPID_DOM_NODE + 6)
#define DISPID_DOM_NODE_FIRSTCHILD             (DISPID_DOM_NODE + 7)
#define DISPID_DOM_NODE_LASTCHILD              (DISPID_DOM_NODE + 8)
#define DISPID_DOM_NODE_PREVIOUSSIBLING        (DISPID_DOM_NODE + 9)
#define DISPID_DOM_NODE_NEXTSIBLING            (DISPID_DOM_NODE + 10)
#define DISPID_DOM_NODE_ATTRIBUTES             (DISPID_DOM_NODE + 11)
#define DISPID_DOM_NODE_INSERTBEFORE           (DISPID_DOM_NODE + 12)
#define DISPID_DOM_NODE_REPLACECHILD           (DISPID_DOM_NODE + 13)
#define DISPID_DOM_NODE_REMOVECHILD            (DISPID_DOM_NODE + 14)
#define DISPID_DOM_NODE_APPENDCHILD            (DISPID_DOM_NODE + 15)
#define DISPID_DOM_NODE_HASCHILDNODES          (DISPID_DOM_NODE + 16)
#define DISPID_DOM_NODE_OWNERDOC               (DISPID_DOM_NODE + 17)
#define DISPID_DOM_NODE_CLONENODE              (DISPID_DOM_NODE + 18)


#define DISPID_DOM_W3CWRAPPERS                 (DISPID_DOM_NODE + 0x20)

#define DISPID_DOM_DOCUMENTFRAGMENT            (DISPID_DOM_W3CWRAPPERS)
#define DISPID_DOM_DOCUMENTFRAGMENT_TOP        (DISPID_DOM_DOCUMENTFRAGMENT + 2)

#define DISPID_DOM_DOCUMENT                        (DISPID_DOM_DOCUMENTFRAGMENT + 0x20)
#define DISPID_DOM_DOCUMENT_DOCTYPE                (DISPID_DOM_DOCUMENT + 1)
#define DISPID_DOM_DOCUMENT_IMPLEMENTATION         (DISPID_DOM_DOCUMENT + 2)
#define DISPID_DOM_DOCUMENT_DOCUMENTELEMENT        (DISPID_DOM_DOCUMENT + 3)
#define DISPID_DOM_DOCUMENT_CREATEELEMENT          (DISPID_DOM_DOCUMENT + 4)
#define DISPID_DOM_DOCUMENT_CREATEDOCUMENTFRAGMENT (DISPID_DOM_DOCUMENT + 5)
#define DISPID_DOM_DOCUMENT_CREATETEXTNODE         (DISPID_DOM_DOCUMENT + 6)
#define DISPID_DOM_DOCUMENT_CREATECOMMENT          (DISPID_DOM_DOCUMENT + 7)
#define DISPID_DOM_DOCUMENT_CREATECDATASECTION     (DISPID_DOM_DOCUMENT + 8)
#define DISPID_DOM_DOCUMENT_CREATEPROCESSINGINSTRUCTION (DISPID_DOM_DOCUMENT + 9)
#define DISPID_DOM_DOCUMENT_CREATEATTRIBUTE        (DISPID_DOM_DOCUMENT + 10)
#define DISPID_DOM_DOCUMENT_CREATEENTITY           (DISPID_DOM_DOCUMENT + 11)
#define DISPID_DOM_DOCUMENT_CREATEENTITYREFERENCE  (DISPID_DOM_DOCUMENT + 12)
#define DISPID_DOM_DOCUMENT_GETELEMENTSBYTAGNAME   (DISPID_DOM_DOCUMENT + 13)
#define DISPID_DOM_DOCUMENT_TOP                    (DISPID_DOM_DOCUMENT + 14)

#define DISPID_DOM_ELEMENT                         (DISPID_DOM_DOCUMENT + 0x20)
#define DISPID_DOM_ELEMENT_GETTAGNAME              (DISPID_DOM_ELEMENT + 1)
#define DISPID_DOM_ELEMENT_GETATTRIBUTES           (DISPID_DOM_ELEMENT + 2)
#define DISPID_DOM_ELEMENT_GETATTRIBUTE            (DISPID_DOM_ELEMENT + 3)
#define DISPID_DOM_ELEMENT_SETATTRIBUTE            (DISPID_DOM_ELEMENT + 4)
#define DISPID_DOM_ELEMENT_REMOVEATTRIBUTE         (DISPID_DOM_ELEMENT + 5)
#define DISPID_DOM_ELEMENT_GETATTRIBUTENODE        (DISPID_DOM_ELEMENT + 6)
#define DISPID_DOM_ELEMENT_SETATTRIBUTENODE        (DISPID_DOM_ELEMENT + 7)
#define DISPID_DOM_ELEMENT_REMOVEATTRIBUTENODE     (DISPID_DOM_ELEMENT + 8)
#define DISPID_DOM_ELEMENT_GETELEMENTSBYTAGNAME    (DISPID_DOM_ELEMENT + 9)
#define DISPID_DOM_ELEMENT_NORMALIZE               (DISPID_DOM_ELEMENT + 10)
#define DISPID_DOM_ELEMENT_TOP                     (DISPID_DOM_ELEMENT + 11)

#define DISPID_DOM_DATA                        (DISPID_DOM_ELEMENT + 0x20)
#define DISPID_DOM_DATA_LENGTH                 (DISPID_DOM_DATA + 1)
#define DISPID_DOM_DATA_SUBSTRING              (DISPID_DOM_DATA + 2)
#define DISPID_DOM_DATA_APPEND                 (DISPID_DOM_DATA + 3)
#define DISPID_DOM_DATA_INSERT                 (DISPID_DOM_DATA + 4)
#define DISPID_DOM_DATA_DELETE                 (DISPID_DOM_DATA + 5)
#define DISPID_DOM_DATA_REPLACE                (DISPID_DOM_DATA + 6)
#define DISPID_DOM_DATA_TOP                    (DISPID_DOM_DATA + 7)

#define DISPID_DOM_ATTRIBUTE                   (DISPID_DOM_DATA + 0x20)
#define DISPID_DOM_ATTRIBUTE_GETNAME           (DISPID_DOM_ATTRIBUTE + 1)
#define DISPID_DOM_ATTRIBUTE_SPECIFIED         (DISPID_DOM_ATTRIBUTE + 2)
#define DISPID_DOM_ATTRIBUTE_GETVALUE          (DISPID_DOM_ATTRIBUTE + 3)
#define DISPID_DOM_ATTRIBUTE_TOP               (DISPID_DOM_ATTRIBUTE + 4)

#define DISPID_DOM_TEXT                (DISPID_DOM_ATTRIBUTE + 0x20)
#define DISPID_DOM_TEXT_SPLITTEXT      (DISPID_DOM_TEXT + 1)
#define DISPID_DOM_TEXT_JOINTEXT       (DISPID_DOM_TEXT + 2)
#define DISPID_DOM_TEXT_TOP            (DISPID_DOM_TEXT + 3)

#define DISPID_DOM_PI           (DISPID_DOM_TEXT + 0x20)
#define DISPID_DOM_PI_TARGET    (DISPID_DOM_PI + 1)
#define DISPID_DOM_PI_DATA      (DISPID_DOM_PI + 2)
#define DISPID_DOM_PI_TOP       (DISPID_DOM_PI + 3)

#define DISPID_DOM_DOCUMENTTYPE            (DISPID_DOM_PI + 0x20)
#define DISPID_DOM_DOCUMENTTYPE_NAME       (DISPID_DOM_DOCUMENTTYPE + 1)
#define DISPID_DOM_DOCUMENTTYPE_ENTITIES   (DISPID_DOM_DOCUMENTTYPE + 2)
#define DISPID_DOM_DOCUMENTTYPE_NOTATIONS  (DISPID_DOM_DOCUMENTTYPE + 3)
#define DISPID_DOM_DOCUMENTTYPE_TOP        (DISPID_DOM_DOCUMENTTYPE + 4)

#define DISPID_DOM_NOTATION                (DISPID_DOM_DOCUMENTTYPE + 0x20)
#define DISPID_DOM_NOTATION_PUBLICID       (DISPID_DOM_NOTATION + 1)
#define DISPID_DOM_NOTATION_SYSTEMID       (DISPID_DOM_NOTATION + 2)
#define DISPID_DOM_NOTATION_TOP            (DISPID_DOM_NOTATION + 3)

#define DISPID_DOM_ENTITY                  (DISPID_DOM_NOTATION + 0x20)
#define DISPID_DOM_ENTITY_PUBLICID         (DISPID_DOM_ENTITY + 1)
#define DISPID_DOM_ENTITY_SYSTEMID         (DISPID_DOM_ENTITY + 2)
#define DISPID_DOM_ENTITY_NOTATIONNAME     (DISPID_DOM_ENTITY + 3)
#define DISPID_DOM_ENTITY_TOP              (DISPID_DOM_ENTITY + 4)

//define DISPID_DOM_COMMENT         
//define DISPID_DOM_CDATASECTION
//define DISPID_DOM_ENTITYREFERENCE

#define DISPID_DOM_W3CWRAPPERS_TOP         (DISPID_DOM_ENTITY + 0x20)
    
#define DISPID_DOM_NODELIST            (DISPID_DOM_W3CWRAPPERS_TOP + 0x20)
#define DISPID_DOM_NODELIST_ITEM       (DISPID_DOM_NODELIST + 1)
#define DISPID_DOM_NODELIST_LENGTH     (DISPID_DOM_NODELIST + 2)

#define DISPID_DOM_NAMEDNODEMAP                    (DISPID_DOM_NODELIST + 0x20)
#define DISPID_DOM_NAMEDNODEMAP_GETNAMEDITEM       (DISPID_DOM_NAMEDNODEMAP + 3)
#define DISPID_DOM_NAMEDNODEMAP_SETNAMEDITEM       (DISPID_DOM_NAMEDNODEMAP + 4)
#define DISPID_DOM_NAMEDNODEMAP_REMOVENAMEDITEM    (DISPID_DOM_NAMEDNODEMAP + 5)


#define DISPID_DOM_IMPLEMENTATION              (DISPID_DOM_NAMEDNODEMAP + 0x20)
#define DISPID_DOM_IMPLEMENTATION_HASFEATURE   (DISPID_DOM_IMPLEMENTATION + 1)

#define DISPID_DOM_TOP         (DISPID_DOM_IMPLEMENTATION + 0x20)

//;begin_internal
#endif // __XMLDOMDID_H__
//;end_internal