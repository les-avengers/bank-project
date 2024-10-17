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
/*   user.c                                        |__ --==|'-''' '...;       */
/*                                                [  ]  :[|       |---\       */
/*   By: teghjyot <teghjyot@teghjyot.com>         |__| I=[|     .'    '.      */
/*                                                / / ____|     :       '._   */
/*   Created: 2024/10/17 11:58:52 by teghjyot    |-/.____.'      | :      :   */
/*   Updated: 2024/10/17 12:39:05 by smail        /___ /___      '-'._----'   */
/*                                                                            */
/* ************************************************************************** */

#include "bank_ops.h"

void	create_user(t_user	*user)
{
	char	temp[256];
	size_t	len;

	printf("Entrer un numero bancaire: ");
	scanf("%s", temp);
    
    len = strlen(temp);
    user->username = (char *)malloc((len + 1) * sizeof(char));
	strlcpy(user->username, temp, len + 1);
	printf("Votre numero bancaire : %s\n", user->username);
	
    bzero(temp, 256);
	len = 0;
	printf("Enter password: ");
	scanf("%s", temp);
	
    len = strlen(temp);
	user->password = (char *)malloc((len + 1) * sizeof(char));
	strlcpy(user->password, temp, len + 1);
	printf("Your password is : %s\n", user->password);
}

void    modify_nameuser(t_user    *user){
    char    temp[256];
    size_t    len;

    printf("Entrer un nouveau numero bancaire: ");
    scanf("%s", temp);
    
    len = strlen(temp);
    user->username = (char *)malloc((len + 1) * sizeof(char));
    strlcpy(user->username, temp, len + 1);
    printf("Votre nouveau numero bancaire est: %s\n", user->username);
    
    
}
