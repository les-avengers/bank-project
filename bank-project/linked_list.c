/* ************************************************************************** */
/*                                                                            */
/*                           .                      .                   ·     */
/*        .    __ _o|                        .                ·               */
/*            |  /__|===--        .                                  ·        */
/*     *      [__|______~~--._                      .                         */
/*      .    |\  `---.__:====]-----...,,_____                *          ·     */
/*           |[>-----|_______<----------_____;::===--             .==.        */
/*           |/_____.....-----'''~~~~~~~                         ()''()-.     */
/*      +               ·                           .---.         ;--; /      */
/*                                                .'_:___". _..'.  __'.       */
/*   bank_ops.h                                    |__ --==|'-''' '...;       */
/*                                                [  ]  :[|       |---\       */
/*   By: teghjyot <teghjyot@teghjyot.com>         |__| I=[|     .'    '.      */
/*                                                / / ____|     :       '._   */
/*   Created: 2024/10/17 11:58:21 by teghjyot    |-/.____.'      | :      :   */
/*   Updated: 2024/10/17 11:58:38 by teghjyot     /___ /___      '-'._----'   */
/*                                                                            */
/* ************************************************************************** */

#include "bank_ops.h"

t_list	*ft_create_node(void *data)
{
	t_list	*head;

	head = NULL;
	if (head)
	{
		head->data = data;
		head->next = NULL;
	}
	return (head);
}


void	ft_list_push_front(t_list **begin_list, void *data)
{
	t_list	*push;

	push = NULL;
	if (*begin_list)
	{
		push = ft_create_node(data);
		if (push)
		{
			push->next = *begin_list;
			*begin_list = push;
		}
	}
	else
		*begin_list = ft_create_node(data);
}

size_t	ft_list_size(t_list *begin_list)
{
	size_t	i;

	i = 0;
	while (begin_list)
	{
		begin_list = begin_list->next;
		i++;
	}
	return (i);
}

t_list	*ft_list_last(t_list *begin_list)
{
	while (begin_list->next)
		begin_list = begin_list->next;
	return (begin_list);
}

void	ft_list_push_back(t_list **begin_list, void *data)
{
	t_list	*list;
	
	list = *begin_list;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = ft_create_node(data);
	}
	else
		*begin_list = ft_create_node(data);
}

t_list	*ft_list_push_strs(size_t size, char **strs)
{
	t_list	*elem;
	t_list	*elem2;
	int		i;

	elem = ft_create_node(strs[0]);
	i = 0;
	while (++i < size)
	{
		elem2 = ft_create_node(strs[i]);
		elem2->next = elem;
		elem = elem2;
	}
	return (elem);
}

void	ft_list_clear(t_list *begin_with, void (*free_fct)(void *))
{
	t_list	*ptr;

	if (begin_with)
		while (begin_with)
		{
			(*free_fct)(begin_with->data);
			ptr = begin_with->next;
			free(begin_with);
			begin_with = ptr;
		}
}

t_list	*ft_list_at(t_list *begin_list, unsigned int nbr)
{
	unsigned int	i;
	
	i = 0;
	while (begin_list)
	{
		if (i == nbr)
			return (begin_list);
		begin_list = begin_list->next;
		i++;
	}
	return (0);
}

void	ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
	while (begin_list)
	{
		(*f)(begin_list->data);
		begin_list = begin_list->next;
	}
}

void	ft_list_foreach_if(t_list *begin_list,
						   void (*f)(void *),
						   void *data_ref, int (*cmp)(void *, void *))
{
	while (begin_list)
	{
		if ((*cmp)(begin_list->data, data_ref) == 0)
			(*f)(begin_list->data);
		begin_list = begin_list->next;
	}
}

t_list	*ft_list_find(t_list *begin_list, void *data_ref, int (*cmp)(void *, void *))
{
	while (begin_list)
	{
		if ((*cmp)(begin_list->data, data_ref) == 0)
			return (begin_list);
		begin_list = begin_list->next;
	}
	return (0);
}

void	ft_list_remove_if(t_list **begin_list,
						  void *data_ref, int (*cmp)(void *, void *), void (*free_fct)(void *))
{
	t_list	*list;
	t_list	*tmp;
	
	while (*begin_list && (*cmp)((*begin_list)->data, data_ref) == 0)
	{
		tmp = *begin_list;
		*begin_list = (*begin_list)->next;
		(*free_fct)(tmp->data);
		free(tmp);
	}
	list = *begin_list;
	while (list && list->next)
	{
		if ((*cmp)(list->next->data, data_ref) == 0)
		{
			tmp = list->next;
			list->next = list->next->next;
			(*free_fct)(tmp->data);
			free(tmp);
		}
		else
			list = list->next;
	}
}
