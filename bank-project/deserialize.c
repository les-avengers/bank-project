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

t_list	*deserialize_account(FILE *file, size_t num_accounts)
{
	t_list	*head;
	t_account	*new_account;
	size_t		i;

	head = NULL;
	i = 0;
	while (i < num_accounts)
	{
		new_account = (t_account *)malloc(sizeof(t_account));
		if (!new_account)
		{
			fprintf(stderr, "Error: Memory allocation for account failed\n");
			break;
		}
		fread(&new_account->acc_no, sizeof(unsigned long), 1, file);
		fread(&new_account->balance, sizeof(double), 1, file);
		fread(&new_account->type, sizeof(e_account_type), 1, file);
		new_account->iban = read_string(file);
		fread(&new_account->creation_time, sizeof(time_t), 1, file);
		ft_list_push_front(&head, new_account);
		i++;
	}
	return (head);
}


t_user *deserialize_user(FILE *file)
{
	t_user	*user;

	user = malloc(sizeof(t_user));
	if (!user)
		return (NULL);
	fread(&user->user_id, sizeof(uint64_t), 1, file);
	user->prénom = read_string(file);
	user->nom = read_string(file);
	user->mots_de_passe = read_string(file);
	user->twofa_secret = read_string(file);
	user->backup_codes = read_string(file);
	fread(&user->numéro_de_téléphone, sizeof(size_t), 1, file);
	fread(&user->balance, sizeof(size_t), 1, file);
	fread(&user->num_accounts, sizeof(size_t), 1, file);
	user->accounts = deserialize_account(file, user->num_accounts);
	if (!user->user_id)
		return (NULL);
	return (user);
}

t_list	*deserialize(FILE *file)
{
	t_list	*head;
	t_user	*user;

	head = NULL;
	user = NULL;
	while (1)
	{
		user = deserialize_user(file);
		if (!user)
			break;
		ft_list_push_front(&head, user);
	}
	return (head);
}
