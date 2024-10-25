/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:03:43 by eschmitz          #+#    #+#             */
/*   Updated: 2024/08/05 15:22:28 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char		*get_next_line(int fd);
char		*read_line(int fd, char *save, char *buffer);
char		*ft_save(char **save);

int			ft_strlen(const char *str);
char		*ft_strchr(const char *str, int c);
char		*ft_strjoin(char *str, char *buffer);
char		*ft_substr(char *s, int start, int len);
char		*ft_strdup(char *str);

#endif