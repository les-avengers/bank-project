//
//  linked_list.h
//  bank-project
//
//  Created by Teghjyot Singh on 12/11/2024.
//

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include <stdlib.h>
# include <string.h>

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

t_list	*ft_create_node(void *data);
void	ft_list_push_front(t_list **begin_list, void *data);
size_t	ft_list_size(t_list *begin_list);
t_list	*ft_list_last(t_list *begin_list);
void	ft_list_clear(t_list *begin_with, void (*free_fct)(void *));
t_list	*ft_list_at(t_list *begin_list, unsigned int nbr);
void	ft_list_foreach(t_list *begin_list, void (*f)(void *));
void	ft_list_foreach_if(t_list *begin_list,
						   void (*f)(void *),
						   void *data_ref, int (*cmp)(void *, void *));
t_list	*ft_list_find(t_list *begin_list, void *data_ref, int (*cmp)(void *, void *));
void	ft_list_remove_if(t_list **begin_list,
						  void *data_ref, int (*cmp)(void *, void *), void (*free_fct)(void *));
void	ft_list_delete_node(t_list **begin_list, t_list *node_to_delete, void (*free_fct)(void *));

#endif
