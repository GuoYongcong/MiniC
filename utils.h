/*
* @Copyright (c), 2020-2020, GuoYongcong.
* @File name: utils.h
* @Description: 该文件声明了创建语法树结点、打印语法树函数
* @Author: 郭永聪
* @Version: 1.0
* @Date:   2020-05-01
* @History:
*   <author>    <version>   <date>    <description>
*/

#ifndef _UTILS_H_
#define _UTILS_H_

//创建语法树结点
struct Node * createSyntaxTreeNode(NodeType, long long, struct Node *, struct Node *, struct Node *);

//打印语法树
void printSyntaxTree( struct Node * );

#endif
