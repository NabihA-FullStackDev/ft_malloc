#include "ft_stdlib.h"

static int is_start_free(void *tmp, t_heap *node, size_t size)
{
  size_t res;

  if (node->block_start < tmp)
  {
    res = tmp - node->block_start;
    if (res >= (size - sizeof(t_block)))
      return (RET_TRUE);
  }
  return (RET_FALSE);
}

static int is_between_free(void *tmp, t_block *end, size_t size)
{
  t_block *t_cpy;
  t_block *res;
  size_t dist;

  t_cpy = tmp;
  res = tmp + sizeof(t_block) + t_cpy->size;
  if (res != end)
  {
    dist = (void *)end - (void *)res;
    if (dist >= size + sizeof(t_block))
      return (RET_TRUE);
  }
  return (RET_FALSE);
}

static int is_heap_end_free(void *tmp, t_heap *node, size_t size)
{
  size_t res;

  res = ((void *)node + node->size_max - sizeof(t_heap)) - (tmp + sizeof(t_block) + ((t_block *)tmp)->size);
  if (res >= (size + sizeof(t_block)))
    return (RET_TRUE);
  return (RET_FALSE);
}

/*
** Verification des emplacement vide de la heap
** renvoi un pointeur s'il y a une zone vide de
** la taille necessaire, sinon renvoie NULL.
**
** Dans le cas ou tmp est non NULL insert permet
** De determiner ou doit il etre inserer ou pas
*/
void *check_for_spot(t_heap **node, size_t size, t_block **insert)
{
  void *tmp;

  tmp = NULL;
  if ((*node)->block_first == NULL)
  {
    tmp = (*node)->block_start;
    (*node)->block_first = (*node)->block_start;
  }
  else
  {
    (*insert) = (*node)->block_first;
    if (is_start_free(*insert, *node, size) == RET_TRUE)
      tmp = (*node)->block_start;
    else
    {
      while ((*insert)->next != NULL && is_between_free(*insert, (*insert)->next, size) == RET_FALSE)
        *insert = (*insert)->next;
      if (((*insert)->next == NULL && is_heap_end_free(*insert, *node, size) == RET_TRUE) || ((*insert)->next != NULL && is_between_free(*insert, (*insert)->next, size) == RET_TRUE))
        tmp = (void *)(*insert) + (*insert)->size + sizeof(t_block);
      else if ((*node)->next != NULL && (*node)->category == (*node)->next->category)
      {
        (*node) = (*node)->next;
        tmp = check_for_spot(node, size, insert);
      }
    }
  }
  return (tmp);
}
