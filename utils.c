#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	i;

	if (!s1 || !set)
		return (0);
	i = 0;
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i--;
	return (ft_substr(s1, 0, i + 1));
}

char	*ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			*k;

	k = (char *)s;
	c = (unsigned char)c;
	i = 0;
	while (k[i])
	{
		if (k[i] == c)
			return (&k[i]);
		i++;
	}
	if (c == 0)
		return (&k[i]);
	return (0);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	int	i;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	int		k;
	int		i;
	char	*str;

	str = (char *)s1;
	i = ft_strlen(str);
	s2 = (char *)malloc(sizeof(char) * (i + 1));
	if (!s2)
		return (0);
	k = 0;
	while (str[k])
	{
		s2[k] = str[k];
		k++;
	}
	s2[k] = '\0';
	return (s2);
}

link_list	*link_lstnew(char *content, char flag)
{
	link_list	*str;

	str = malloc(sizeof(link_list));
	if (!str)
		return (0);
	str->content = content;
	str->flag = flag;
	str->next = NULL;
	return (str);
}

void	link_lstadd_back(link_list **lst, link_list *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	link_lstlast(*lst)->next = new;
}

link_list	*link_lstlast(link_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	link_lstclear(link_list **lst)
{
	link_list	*tmp;

	if (!lst)
	{
		return ;
	}
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		link_lstdelone(*lst);
		*lst = tmp;
	}
}

void	link_lstdelone(link_list *lst)
{
	if (!lst)
		return ;
		
	free(lst->content);
	free(lst);
}