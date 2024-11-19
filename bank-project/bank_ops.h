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
/*   Updated: 2024/10/17 16:17:14 by smail        /___ /___      '-'._----'   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef BANK_OPS_H
# define BANK_OPS_H


# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdbool.h>
# include <math.h>
# include <time.h>
# include "account.h"
# include "serialize.h"
# include "deserialize.h"
# include "user.h"

typedef enum
{
	LOGIN = 1,
	CREATE_ACCOUNT,
	VIEW_ACCOUNT_OPTIONS,
	CREATE_ACCOUNT_OPTION,
	DELETE_USER,
	LOGOUT,
	VIEW_BALANCE,
	MANAGE_ACCOUNTS,
	DEPOSIT_MONEY,
	WITHDRAW_MONEY,
	TRANSFER_MONEY,
	VIEW_HISTORY,
	DELETE_ACCOUNT,
	CHOOSE_ACC,
	SAVE_EXIT,
	INVALID_OPTION = -1
}	e_options;

typedef enum
{
	COMPTE_COURANT,
	LIVRET_EPARGNE
}	e_account_type;

typedef struct	s_account
{
	unsigned long	acc_no;
	double			balance;
	e_account_type	type;
	char			*iban;
	time_t			creation_time;
}	t_account;

typedef struct	s_user
{
	unsigned long long	user_id;
	char				*prénom;
	char				*nom;
	char				*mots_de_passe;
	char				*twofa_secret;
	char				*backup_codes;
	unsigned long		numéro_de_téléphone;
	size_t				balance;
	t_list				*accounts;
	size_t				num_accounts;
}	t_user;

void			create_account(t_user *user);
void			user_login(t_list *users, unsigned long long *logged_in);
void			user_logout(unsigned long long *logged_in);
void			view_balance(t_user *user);
unsigned long	choose_account(t_user *user);
void			print_history(t_user *user, unsigned long i);
void			transfer(t_list *users, t_user **user, unsigned long i);
void			delete_account(t_user **user, unsigned long i);
void			delete_user(t_list **users, t_user **user);
int				find_user(void *data, void *user_id);

void	create_user(t_list **users);
void    set_balance(t_user *user);
void    voir_balance(t_user *user);
void    depot(t_user **user, unsigned long i);
void    retrait(t_user **user, unsigned long i);
void    modify_password(t_user *user);
void    afficher_user(t_user *user);
void    afficher_password(t_user *user);
void    parametres(t_user *user);
void	get_string(const char *prompt, char **dest);

# endif
