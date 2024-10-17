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

#ifndef BANK_OPS_H
# define BANK_OPS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>

typedef struct s_user {
	char	*username;
	char	*password;
	size_t	balance;
	char	*history;
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
