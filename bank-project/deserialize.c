//
//  deserialize.c
//  bank-project
//
//  Created by Teghjyot Singh on 12/11/2024.
//

#include "deserialize.h"

char	*read_string(FILE *file)
{
	size_t	len;
	char	*str;

	fread(&len, sizeof(size_t), 1, file);
	if (len == 0)
		return NULL;
	str = (char *)malloc(len + 1);
	if (str)
	{
		fread(str, sizeof(char), len, file);
		str[len] = '\0';
	}
	return (str);
}

t_account *deserialize_account(FILE *file, size_t num_accounts)
{
	t_account		*account = NULL;
	t_account		*tail = NULL;
	unsigned long	acc_no;
	double			balance;
	char			*type;

	for (size_t i = 0; i < num_accounts; ++i)
	{
		size_t		read_count;
		t_account	*new_account;
		read_count = fread(&acc_no, sizeof(unsigned long), 1, file);
		if (read_count != 1)
			break;
		read_count = fread(&balance, sizeof(double), 1, file);
		if (read_count != 1)
			break;
		type = read_string(file);
		if (!type) break;
		
		new_account = (t_account *)malloc(sizeof(t_account));
		if (!new_account)
		{
			fprintf(stderr, "Error: Memory allocation for account failed\n");
			break;
		}
		new_account->acc_no = acc_no;
		new_account->balance = balance;
		new_account->type = type;
		new_account->next = NULL;
		
		if (tail)
			tail->next = new_account;
		else
			account = new_account;
		tail = new_account;
	}
	return (account);
}


t_user *deserialize_user(FILE *file)
{
	size_t	len;
	t_user	*user;

	user = malloc(sizeof(t_user));
	if (!user)
		return NULL;
	if (fread(&len, sizeof(size_t), 1, file) != 1)
		return NULL;
	user->prénom = malloc(len);
	if (!user->prénom)
		return NULL;
	if (fread(user->prénom, sizeof(char), len, file) != len)
		return NULL;
	if (fread(&len, sizeof(size_t), 1, file) != 1)
		return NULL;
	user->nom = malloc(len);
	if (!user->nom)
		return NULL;
	if (fread(user->nom, sizeof(char), len, file) != len)
		return NULL;
	if (fread(&len, sizeof(size_t), 1, file) != 1)
		return NULL;
	user->mots_de_passe = malloc(len);
	if (!user->mots_de_passe)
		return NULL;
	if (fread(user->mots_de_passe, sizeof(char), len, file) != len)
		return NULL;
	if (fread(&user->numéro_de_téléphone, sizeof(unsigned long), 1, file) != 1)
		return NULL;
	if (fread(&user->balance, sizeof(size_t), 1, file) != 1)
		return NULL;
	if (fread(&user->num_accounts, sizeof(size_t), 1, file) != 1)
		return NULL;
	user->accounts = deserialize_account(file, user->num_accounts);
	return (user);
}

t_list *deserialize(FILE *file)
{
	t_list	*head = NULL;
	t_list	*tail = NULL;
	
	while (1)
	{
		t_list	*new_node;
		t_user	*user;

		user = deserialize_user(file);
		if (!user)
			break;
		new_node = ft_create_node(user);
		if (!new_node)
		{
			fprintf(stderr, "Error creating node\n");
			break;
		}
		if (tail)
			tail->next = new_node;
		else
			head = new_node;
		tail = new_node;
	}
	
	return head;
}
