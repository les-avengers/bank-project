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
/*   Updated: 2024/10/17 16:17:52 by smail        /___ /___      '-'._----'   */
/*                                                                            */
/* ************************************************************************** */

#include "bank_ops.h"

void	create_user(t_user	*user)
{
	char	temp[256];
	size_t	len;

	printf("Enter username: ");
	scanf("%s", temp);
	len = strlen(temp);
	user->username = (char *)malloc((len + 1) * sizeof(char));
	strlcpy(user->username, temp, len + 1);
	printf("Your username is : %s\n", user->username);
	bzero(temp, 256);
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


void    modify_password(t_user    *user){
    char    temp[256];
    size_t    len;

    printf("Enter password: ");
    scanf("%s", temp);
    
    len = strlen(temp);
    user->password = (char *)malloc((len + 1) * sizeof(char));
    strlcpy(user->password, temp, len + 1);
    printf("Your password is : %s\n", user->password);
    
    
}


void set_balance(t_user *user){
    
    int temp;
    
    printf("Entrer le solde de votre compte: ");
    scanf("%d", &temp);
    
    user->balance = temp;
    
}

void voir_balance(t_user *user){
    
    printf("Votre solde: %zu \n ",user->balance);
}


void depot(t_user *user){
    int temp;
    
    printf("Entrer le nombre d'argent que vous voulez deposer: ");
    scanf("%d", &temp);
    
    user->balance += temp;
    
    printf("Voici le nouveau solde de votre compte: %zu \n", user->balance);
    
    
}

void retrait(t_user *user){
    int temp;
    
    printf("Entrer le nombre d'argent que vous voulez retirer: ");
    scanf("%d", &temp);
    
    user->balance -= temp;
    
    printf("Voici le nouveau solde de votre compte: %zu \n", user->balance);
    
    
}

void    afficher_user(t_user *user){
    
    printf("Votre numero bancaire est: %s\n", user->username);
    
}

void    afficher_password(t_user *user){
    
    printf("Votre mot de passe est: %s\n", user->password);
    
}



