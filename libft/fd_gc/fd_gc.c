/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_gc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkadir <aelkadir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 02:08:09 by aelkadir          #+#    #+#             */
/*   Updated: 2025/03/20 02:35:52 by aelkadir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd_gc	**ft_fd_gc(void)
{
	static t_fd_gc	*head = NULL;
	return (&head);
}
void register_fd(int fd)
{
    t_fd_gc	**head;
    t_fd_gc	*new_node;

    if (fd < 0)
        return ;
    head = ft_fd_gc();
    new_node = ft_malloc(sizeof(t_fd_gc));
    if (!new_node)
        exit(1);
    new_node->fd = fd;
    new_node->next = *head;
    *head = new_node;
}
void close_all_fds(void)
{
    t_fd_gc	**head;
    t_fd_gc	*curr;
    t_fd_gc	*temp;

    head = ft_fd_gc();
    curr = *head;
    while (curr)
    {
        close(curr->fd);
        temp = curr;
        curr = curr->next;
        ft_free_one(temp);
    }
    *head = NULL;
}
void unregister_fd(int fd)
{
    t_fd_gc	**head;
    t_fd_gc	*curr;
    t_fd_gc	*prev;

    head = ft_fd_gc();
    curr = *head;
    prev = NULL;
    while (curr)
    {
        if (curr->fd == fd)
        {
            if (prev)
                prev->next = curr->next;
            else
                *head = curr->next;
            ft_free_one(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}