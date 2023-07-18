#include "minishell.h"

void	lexer()
{
	int i;

	char *line;
	i = 0;
	t_list.trimmed = ft_strtrim(t_list.str, " ");
	line = t_list.trimmed;
	int	len;
	int k;
	int flag;
	link_lstclear(&t_list.lst);
	if (!ft_strlen(t_list.trimmed))
		return ;
	while (i < ft_strlen(line))
	{
		flag = 0;
		if ((line[i] == ' ' || line[i] == '\t') && line[i])
			i++;
		else if ((line[i] == '<' || line[i] == '>' || line[i] == '|') && line[i])
		{
			if ((line[i] == '<' || line[i] == '>' || line[i] == '|') && line[i])
			{
				if ((line[i + 1] == '<' || line[i + 1] == '>' || line[i + 1] == '|') && line[i])
					f_parsel(line, &i);
				else
				{
					t_list.holder = (char *)malloc(sizeof(char) * 2);
					t_list.holder[0] = line[i];
					t_list.holder[1] = '\0';
					t_list.parsel_flag = line[i];
					i++;
				}
			}
			flag = 1;
		}
		else if (line[i] != '<' && line[i] != '>' && line[i] != '|' && line[i] != ' ' && line[i] != '\t' && line[i] != 34 && line[i] != 39 && line[i])
		{
			len = i;
			k = 0;
			while (line[len] != ' ' && line[len] != '\t' && line[len] && line[len] != '<' && line[len] != '>' && line[len] != '|' && line[len] != 39 && line[len] != 34)
			{
				len++;
			}
			t_list.holder = (char *)malloc(sizeof(char) * (len - i + 1));
			while (i < len)
			{
				t_list.holder[k] = line[i];
				k++;
				i++;
			}
			t_list.holder[k] = '\0';
			t_list.parsel_flag = 's';
			flag = 1;
		}
		else if (line[i] == 34 || line[i] == 39)
		{
			if (line[i] == 34)
			{
				len = i + 1;
				k = 0;
				t_list.parsel_flag = line[i];
				while (line[len] != t_list.parsel_flag)
				{
					len++;
				}
				t_list.holder = (char *)malloc(sizeof(char) * (len - i + 2));
				while (i <= len)
				{
					t_list.holder[k] = line[i];
					k++;
					i++;
				}
				t_list.holder[k] = '\0';
				t_list.parsel_flag = 34;
			}
			else
			{
				len = i + 1;
				k = 0;
				t_list.parsel_flag = line[i];
				while (line[len] != t_list.parsel_flag)
					len++;
				t_list.holder = (char *)malloc(sizeof(char) * (len - i + 2));
				while (i <= len)
				{
					t_list.holder[k] = line[i];
					i++;
					k++;
				}
				t_list.holder[k] = '\0';
				t_list.parsel_flag = 39;
			}
		flag = 1;
		}
		if (flag == 1)
		{
			link_lstadd_back(&t_list.lst, link_lstnew(t_list.holder, t_list.parsel_flag));
		}
	}
	link_list *a;
	a = t_list.lst;
	printf("----------Liste_Ekrana_Bastırılıyor!---------\n");
	while (a)
	{
		printf("%s    ", a->content);
		//printf("  **%d**    ", tmp->extra_flag);
		printf("----%c----\n", a->flag);
		a = a->next;
	}
	printf("----------Liste_Ekrana_Bastırıldı!---------\n");
}

void	f_parsel(char *line, int *i)
{
	int k;

	k = *i;
	if (line[k] == '|')
	{
		t_list.holder = (char *)malloc(sizeof(char) * 2);
		t_list.holder[0] = line[k];
		t_list.holder[1] = '\0';
		t_list.parsel_flag = '|';
		k++;
	}
	else if (line[k] == '>')
	{
		if (line[k + 1] == '>')
		{
			t_list.holder = (char *)malloc(sizeof(char) * 3);
			t_list.holder[0] = '>';
			t_list.holder[1] = '>';
			t_list.holder[2] = '\0';
			t_list.parsel_flag = 'a';
			k += 2;
		}
		else
		{
			t_list.holder = (char *)malloc(sizeof(char) * 2);
			t_list.holder[0] = line[k];
			t_list.holder[1] = '\0';
			t_list.parsel_flag = '>';
			k++;
		}
	}
	else if (line[k] == '<')
	{
		if (line[k + 1] == '<')
		{
			t_list.holder = (char *)malloc(sizeof(char) * 3);
			t_list.holder[0] = '<';
			t_list.holder[1] = '<';
			t_list.holder[2] = '\0';
			t_list.parsel_flag = 'b';
			k += 2;
		}
		else
		{
			t_list.holder = (char *)malloc(sizeof(char) * 2);
			t_list.holder[0] = '<';
			t_list.holder[1] = '\0';
			t_list.parsel_flag = '<';
			k++;
		}
	}
	*i = k;
}