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
/*   main.c                                        |__ --==|'-''' '...;       */
/*                                                [  ]  :[|       |---\       */
/*   By: teghjyot <teghjyot@teghjyot.com>         |__| I=[|     .'    '.      */
/*                                                / / ____|     :       '._   */
/*   Created: 2024/10/17 11:59:16 by teghjyot    |-/.____.'      | :      :   */
/*   Updated: 2024/10/17 16:17:14 by smail        /___ /___      '-'._----'   */
/*                                                                            */
/* ************************************************************************** */

#include "bank_ops.h"
#include "linked_list.h"

void	show_main_menu(void)
{
	printf("\n=== Système Bancaire ===\n");
	printf("%d. Se Connecter\n", LOGIN);
	printf("%d. Créer un Compte\n", CREATE_ACCOUNT);
	printf("%d. Sauvegarder et Quitter\n", SAVE_EXIT);
	printf("=======================\n");
	printf("Entrez votre choix : ");
}

void	show_transfer_menu(void)
{
	printf("\n=== Gestion des Transferts ===\n");
	printf("%d. Déposer de l'Argent\n", DEPOSIT_MONEY);
	printf("%d. Retirer de l'Argent\n", WITHDRAW_MONEY);
	printf("%d. Transférer de l'Argent\n", TRANSFER_MONEY);
	printf("%d. Voir l'Historique des Transactions\n", VIEW_HISTORY);
	printf("%d. Supprimer un Compte\n", DELETE_ACCOUNT);
	printf("%d. Choisir un autre compte\n", CHOOSE_ACC);
	printf("===========================\n");
	printf("Entrez votre choix : ");
}

void	show_acc_man_menu(void)
{
	printf("\n=== Gestion du Compte ===\n");
	printf("%d. Créer un Autre Compte\n", CREATE_ACCOUNT_OPTION);
	printf("%d. Supprimer l'Utilisateur\n", DELETE_USER);
	printf("%d. Se Déconnecter\n", LOGOUT);
	printf("%d. Voir le Solde\n", VIEW_BALANCE);
	printf("%d. Gérer vos Comptes\n", MANAGE_ACCOUNTS);
	printf("%d. Sauvegarder et Quitter\n", SAVE_EXIT);
	printf("===========================\n");
	printf("Entrez votre choix : ");
}

int main(void)
{
	t_list				*users;
	t_list				*node;
	e_options			choice;
	unsigned long		index;
	unsigned long long	logged_in;
	FILE				*file;
	e_options			view_window;

	srand((unsigned int)time(NULL));
	file = fopen("user_accounts.bin", "rb+");
	if (file == NULL) {
		if ((file = fopen("user_accounts.bin", "wb+")) == NULL)
		{
			perror("Impossible d'ouvrir le fichier en lecture/écriture");
			return (1);
		}
		users = NULL;
	} else {
		users = deserialize(file);
	}
	choice = INVALID_OPTION;
	view_window = INVALID_OPTION;
	logged_in = 0;
	do
	{
		if (logged_in == 0)
		{
			show_main_menu();
			scanf("%d", &choice);
			getchar();
			switch (choice)
			{
				case LOGIN:
					user_login(users, &logged_in);
					break;
				case CREATE_ACCOUNT:
					create_user(&users);
					break;
				case SAVE_EXIT:
					serialize(users, file);
					return (0);
				default:
					printf("Choix invalide. Veuillez réessayer.\n");
			}
		}
		else if (view_window == MANAGE_ACCOUNTS)
		{
			show_transfer_menu();
			scanf("%d", &choice);
			getchar();
			node = ft_list_find(users, (void *)logged_in, &find_user);
			if (node == NULL || node->data == NULL) {
				printf("Utilisateur non trouvé ou données utilisateur invalides.\n");
				continue;
			}
			t_user *user = (t_user *)node->data;
			index = choose_account(user);
			if (index >= user->num_accounts)
			{
				printf("L'index du compte n'existe pas\n");
				view_window = INVALID_OPTION;
				continue;
			}
			switch (choice)
			{
				case DEPOSIT_MONEY:
					depot(&user, index);
					break;
				case WITHDRAW_MONEY:
					retrait(&user, index);
					break;
				case TRANSFER_MONEY:
					transfer(users, &user, index);
					break;
				case VIEW_HISTORY:
					print_history(user, index);
					break;
				case DELETE_ACCOUNT:
					delete_account(&user, index);
					view_window = INVALID_OPTION;
					break;
				case CHOOSE_ACC:
					view_window = INVALID_OPTION;
					break;
				default:
					printf("Option invalide. Veuillez réessayer.\n");
					break;
			}
		}
		else
		{
			show_acc_man_menu();
			scanf("%d", &choice);
			getchar();
			node = ft_list_find(users, (void *)logged_in, &find_user);
			if (node == NULL || node->data == NULL) {
				printf("Utilisateur non trouvé ou données utilisateur invalides.\n");
				continue;
			}
			t_user *user = (t_user *)node->data;
			switch (choice)
			{
				case CREATE_ACCOUNT_OPTION:
					create_account(user);
					break;
				case DELETE_USER:
					delete_user(&users, &user);
					break;
				case LOGOUT:
					user_logout(&logged_in);
					break;
				case VIEW_BALANCE:
					view_balance(user);
					break;
				case MANAGE_ACCOUNTS:
					view_window = MANAGE_ACCOUNTS;
					break;
				case SAVE_EXIT:
					serialize(users, file);
					return (0);
				default:
					printf("Option invalide. Veuillez réessayer.\n");
					break;
			}
		}
	}
	while (choice != SAVE_EXIT);
	return (1);
}
