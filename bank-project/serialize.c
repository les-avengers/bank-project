//
//  serialize.c
//  bank-project
//
//  Created by Teghjyot Singh on 12/11/2024.
//

#include "serialize.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bank_ops.h"

void write_string(FILE *file, const char *str)
{
	size_t	len;
	size_t	written_len;

	if (file == NULL)
	{
		fprintf(stderr, "Error: File pointer is NULL\n");
		return;
	}
	if (str)
		len = strlen(str);
	else
		len = 0;
	written_len = fwrite(&len, sizeof(size_t), 1, file);
	if (written_len != 1)
	{
		fprintf(stderr, "Error writing string length to file\n");
		return;
	}
	if (len > 0) {
		size_t written_str = fwrite(str, sizeof(char), len, file);
		if (written_str != len)
		{
			fprintf(stderr, "Error writing string data to file\n");
			return;
		}
	}
}

void	serialize_account_list(FILE *file, t_list *accounts)
{
	t_account	*account;
	t_list		*current_accounts;

	current_accounts = accounts;
	account = NULL;
	while (current_accounts != NULL)
	{
		account = (t_account *)current_accounts->data;
		fwrite(&account->acc_no, sizeof(unsigned long), 1, file);
		fwrite(&account->balance, sizeof(double), 1, file);
		fwrite(&account->type, sizeof(e_account_type), 1, file);
		write_string(file, account->iban);
		fwrite(&account->creation_time, sizeof(time_t), 1, file);
		current_accounts = current_accounts->next;
	}
}

void serialize_user(FILE *file, t_user *user)
{
	fwrite(&user->user_id, sizeof(uint64_t), 1, file);
	write_string(file, user->prénom);
	write_string(file, user->nom);
	write_string(file, user->mots_de_passe);
	write_string(file, user->twofa_secret);
	write_string(file, user->backup_codes);
	fwrite(&user->numéro_de_téléphone, sizeof(unsigned long), 1, file);
	fwrite(&user->balance, sizeof(size_t), 1, file);
	fwrite(&user->num_accounts, sizeof(size_t), 1, file);
	serialize_account_list(file, user->accounts);
}

void serialize(t_list *begin_list, FILE *file)
{
	t_list *current = begin_list;
	
	while (current != NULL)
	{
		serialize_user(file, (t_user *)current->data);
		current = current->next;
	}
}
