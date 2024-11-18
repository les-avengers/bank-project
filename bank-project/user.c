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
#include "user.h"

unsigned long long	generate_unique_id(void)
{
	static unsigned long long	counter;
	unsigned long long			timestamp;
	unsigned long long			id;
	
	timestamp = (uint64_t)time(NULL);
	if (timestamp % 1000 == 0)
		counter = 0;
	id = (timestamp << 16) | (counter++);
	return (id);
}

void	get_string(const char *prompt, char **dest)
{
	char	temp[256];

	printf("%s", prompt);
	fgets(temp, sizeof(temp), stdin);
	temp[strcspn(temp, "\n")] = 0;
	*dest = strdup(temp);
}

void	user_receipt(t_user	*user)
{
	if (user == NULL)
	{
		printf("Error: User data is NULL.\n");
		return;
	}
	printf("Your account was successfully created.\n");
	printf("User ID: %llu\n", user->user_id);
	printf("Name: %s %s\n", user->prénom, user->nom);
	printf("Phone Number: %lu\n", user->numéro_de_téléphone);

	if (user->num_accounts > 0)
	{
		printf("You have %zu account(s):\n", user->num_accounts);
		t_list *current_account = user->accounts;
		for (size_t i = 0; current_account != NULL; ++i)
		{
			t_account *account = (t_account *)current_account->data;
			printf("Account #%zu:\n", i + 1);
			printf("\tAccount Number: %lu\n", account->acc_no);
			printf("\tAccount Type: ");
			switch (account->type)
			{
				case COMPTE_COURANT:
					printf("Current Account\n");
					break;
				case LIVRET_EPARGNE:
					printf("Savings Account\n");
					break;
				default:
					printf("Unknown Type\n");
					break;
			}
			printf("\tBalance: %.2f\n", account->balance);
			printf("\tIBAN: %s\n", account->iban);
			printf("\tCreated: %s", ctime(&account->creation_time));
			current_account = current_account->next;
		}
	}
	else
		printf("No accounts have been created yet.\n");
	printf("\nThank you for using our service!\n");
}

void	create_user(t_list **users)
{
	t_user	*user;

	user = (t_user *)malloc(sizeof(t_user));
	user->user_id = generate_unique_id();
	getchar();
	get_string("Entrez votre prénom: ", &user->prénom);
	get_string("Entrez votre nom: ", &user->nom);
	printf("Entrez votre numéro de téléphone: ");
	scanf("%ld", &user->numéro_de_téléphone);
	getchar();
	get_string("Entrez vos mots de passe: ", &user->mots_de_passe);
	create_account(user);
	user->num_accounts = ft_list_size(user->accounts);
	user_receipt(user);
	ft_list_push_front(users, user);
}

void	user_login(t_list *users, unsigned long long *logged_in)
{
	char	*uid;
	char	*pwd;
	t_list	*current;
	t_user	*user;

	getchar();
	get_string("uid: ", &uid);
	get_string("pwd: ", &pwd);
	current = users;
	while (current != NULL)
	{
		user = (t_user *)current->data;
		if (atoll(uid) && user->user_id
			&& !strncmp(pwd, user->mots_de_passe, strlen(pwd)))
		{
			*logged_in = user->user_id;
			printf("Bienvenue %s %s!\n", user->prénom, user->nom);
			break;
		}
		else
			*logged_in = 0;
		current = current->next;
	}
}

void	user_logout(unsigned long long *logged_in)
{
	*logged_in = 0;
	printf("You have logged out successfully.\n");
}

//
//void	print_user(void *data)
//{
//	t_user *user = (t_user *)data;
//	
//	printf("\nFirst Name: %s\n", user->prénom ? user->prénom : "N/A");
//	printf("Last Name: %s\n", user->nom ? user->nom : "N/A");
//	printf("Password: %s\n", user->mots_de_passe ? user->mots_de_passe : "N/A");
//	printf("Phone Number: %lu\n", user->numéro_de_téléphone);
//	printf("Balance: %zu\n", user->balance);
//	printf("History: %s\n", user->history ? user->history : "N/A");
//	printf("Account Number: %lu\n", user->acc_no);
//	printf("\n");
//}

// ------------------------------------

//void	create_user(t_user	*user)
//{
//	char	temp[256];
//	size_t	len;
//
//	printf("Enter username: ");
//	scanf("%s", temp);
//	len = strlen(temp);
//	user->username = (char *)malloc((len + 1) * sizeof(char));
//	strlcpy(user->username, temp, len + 1);
//	printf("Your username is : %s\n", user->username);
//	bzero(temp, 256);
//	printf("Enter password: ");
//	scanf("%s", temp);
//	len = strlen(temp);
//	user->password = (char *)malloc((len + 1) * sizeof(char));
//	strlcpy(user->password, temp, len + 1);
//	printf("Your password is : %s\n", user->password);
//}

//
//void    modify_nameuser(t_user    *user){
//    char    temp[256];
//    size_t    len;
//
//    printf("Entrer un nouveau numero bancaire: ");
//    scanf("%s", temp);
//    
//    len = strlen(temp);
//    user->username = (char *)malloc((len + 1) * sizeof(char));
//    strlcpy(user->username, temp, len + 1);
//    printf("Votre nouveau numero bancaire est: %s\n", user->username);
//    
//    
//}
//
//
//void    modify_password(t_user    *user){
//    char    temp[256];
//    size_t    len;
//
//    printf("Enter password: ");
//    scanf("%s", temp);
//    
//    len = strlen(temp);
//    user->password = (char *)malloc((len + 1) * sizeof(char));
//    strlcpy(user->password, temp, len + 1);
//    printf("Your password is : %s\n", user->password);
//    
//    
//}
//
//
//void set_balance(t_user *user){
//    
//    int temp;
//    
//    printf("Entrer le solde de votre compte: ");
//    scanf("%d", &temp);
//    
//    user->balance = temp;
//    
//}
//
//void voir_balance(t_user *user){
//    
//    printf("Votre solde: %zu \n ",user->balance);
//}
//
//
//void depot(t_user *user){
//    int temp;
//    
//    printf("Entrer le nombre d'argent que vous voulez deposer: ");
//    scanf("%d", &temp);
//    
//    user->balance += temp;
//    
//    printf("Voici le nouveau solde de votre compte: %zu \n", user->balance);
//    
//    
//}
//
//void retrait(t_user *user){
//    int temp;
//    
//    printf("Entrer le nombre d'argent que vous voulez retirer: ");
//    scanf("%d", &temp);
//    
//    user->balance -= temp;
//    
//    printf("Voici le nouveau solde de votre compte: %zu \n", user->balance);
//    
//    
//}
//
//void    afficher_user(t_user *user){
//    
//    printf("Votre numero bancaire est: %s\n", user->username);
//    
//}
//
//void    afficher_password(t_user *user){
//    
//    printf("Votre mot de passe est: %s\n", user->password);
//    
//}
//
//
//
