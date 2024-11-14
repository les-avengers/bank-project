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
# include "account.h"
# include "serialize.h"
# include "deserialize.h"
# include "user.h"


typedef struct	s_account
{
	unsigned long		acc_no;
	double				balance;
	char				*type;
	struct s_account	*next;
}	t_account;

typedef struct	s_user
{
	char			*prénom;
	char			*nom;
	char			*mots_de_passe;
	unsigned long	numéro_de_téléphone;
	size_t			balance;
	t_account		*accounts;
	size_t			num_accounts;
}	t_user;


void    menu(t_user *user);
void	create_user(t_user	*user);
void    modify_nameuser(t_user *user);
void    set_balance(t_user *user);
void    voir_balance(t_user *user);
void    depot(t_user *user);
void    retrait(t_user *user);
void    modify_password(t_user *user);
void    afficher_user(t_user *user);
void    afficher_password(t_user *user);
void    parametres(t_user *user);

# endif
