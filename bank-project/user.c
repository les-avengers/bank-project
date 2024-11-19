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

int	find_user(void *data, void *user_id)
{
	if (((t_user *)data)->user_id == (unsigned long long)user_id)
		return (0);
	return (1);
}

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

void user_receipt(t_user *user)
{
	if (user == NULL)
	{
		printf("Erreur : Les données de l'utilisateur sont NULL.\n");
		return;
	}
	printf("\n=== Récapitulatif de l'Utilisateur ===\n");
	printf("Compte créé avec succès.\n");
	printf("ID Utilisateur : %llu\n", user->user_id);
	printf("Nom : %s %s\n", user->prénom, user->nom);
	printf("Numéro de téléphone : %lu\n", user->numéro_de_téléphone);
	if (user->num_accounts > 0)
	{
		printf("Vous avez %zu compte(s) :\n", user->num_accounts);
		t_list *current_account = user->accounts;
		for (size_t i = 0; current_account != NULL; ++i)
		{
			t_account *account = (t_account *)current_account->data;
			printf("\nCompte #%zu :\n", i + 1);
			printf("\tNuméro de Compte : %lu\n", account->acc_no);
			printf("\tType de Compte : ");
			switch (account->type)
			{
				case COMPTE_COURANT:
					printf("Compte Courant\n");
					break;
				case LIVRET_EPARGNE:
					printf("Compte d'Épargne\n");
					break;
				default:
					printf("Type Inconnu\n");
					break;
			}
			printf("\tSolde : %.2f EUR\n", account->balance);
			printf("\tIBAN : %s\n", account->iban);
			printf("\tCréé le : %s", ctime(&account->creation_time));
			current_account = current_account->next;
		}
	}
	else
		printf("Aucun compte n'a été créé pour le moment.\n");
	printf("\nMerci d'utiliser notre service !\n");
}

void	create_user(t_list **users)
{
	t_user	*user;
	
	user = (t_user *)malloc(sizeof(t_user));
	user->user_id = generate_unique_id();
	getchar();
	get_string("Entrez votre prénom : ", &user->prénom);
	get_string("Entrez votre nom : ", &user->nom);
	printf("Entrez votre numéro de téléphone : ");
	scanf("%ld", &user->numéro_de_téléphone);
	getchar();
	get_string("Entrez vos mots de passe : ", &user->mots_de_passe);
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

	get_string("Identifiant : ", &uid);
	get_string("Mot de passe : ", &pwd);
	current = users;
	while (current != NULL)
	{
		user = (t_user *)current->data;
		if ((unsigned long long)atoll(uid) == user->user_id && strcmp(pwd, user->mots_de_passe) == 0)
		{
			*logged_in = user->user_id;
			printf("Bienvenue %s %s !\n", user->prénom, user->nom);
			free(uid);
			free(pwd);
			return;
		}
		current = current->next;
	}
	*logged_in = 0;
	printf("Identifiant ou mot de passe incorrect. Veuillez réessayer.\n");
	free(uid);
	free(pwd);
}

void	user_logout(unsigned long long *logged_in)
{
	*logged_in = 0;
	printf("Vous vous êtes déconnecté avec succès.\n");
}

void	delete_user(t_list **users, t_user **user)
{
	t_list		*current_acc;
	
	current_acc = (*user)->accounts;
	while (current_acc != NULL)
	{
		current_acc = current_acc->next;
		delete_account(user, 0);
	}
	if ((*user)->prénom)
		free((*user)->prénom);
	if ((*user)->nom)
		free((*user)->nom);
	if ((*user)->mots_de_passe)
		free((*user)->mots_de_passe);
	if ((*user)->twofa_secret)
		free((*user)->twofa_secret);
	if ((*user)->backup_codes)
		free((*user)->backup_codes);
	ft_list_clear((*user)->accounts, free);
	ft_list_delete_node(users, ft_list_find(*users, (void *)*user, &find_user), free);
	if (user && *user)
		free(*user);
}
