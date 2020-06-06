#include "globals.h"
#include "stack.h"

//链表节点定义
typedef struct LinkNode
{
    Loc scope;
    struct LinkNode *next;
} * LNode; //LinkNode

static LNode top = NULL;

//进栈
bool push(Loc *scope)
{
    LNode l = (LNode)malloc(sizeof(struct LinkNode));
    if (NULL == l)
    { //如果空间分配失败
        return false;
    } //if
    l->scope.first_line = scope->first_line;
    l->scope.first_column = scope->first_column;
    l->scope.last_line = scope->last_line;
    l->scope.last_column = scope->last_column;
    l->next = top;
    top = l;
    return true;
}

//出栈
void pop()
{
    if (NULL == top)
    { //如果栈空
        return;
    }
    LNode l = top;
    top = top->next;
    free(l);
}

//读取栈顶元素值
Loc *getTop()
{
    if (NULL == top)
    { //如果栈空
        return 0;
    } //if
    return &top->scope;
}

//清空栈
void makeEmpty()
{
    LNode l;
    while (NULL != top)
    {
        l = top;
        top = top->next;
        free(l);
    }
}
