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

void show_main_menu(void)
{
	printf("\n=== Banking System ===\n");
	printf("%d. Login\n", LOGIN);
	printf("%d. Create Account\n", CREATE_ACCOUNT);
	printf("%d. Save and Exit\n", SAVE_EXIT);
	printf("=======================\n");
	printf("Enter your choice: ");
}

void show_transfer_menu(void)
{
	printf("\n=== Transfer Management ===\n");
	printf("%d. Deposit Money\n", DEPOSIT_MONEY);
	printf("%d. Withdraw Money\n", WITHDRAW_MONEY);
	printf("%d. Transfer Money\n", TRANSFER_MONEY);
	printf("%d. View Transaction History\n", VIEW_HISTORY);
	printf("===========================\n");
	printf("Enter your choice: ");
}

void show_acc_man_menu(void)
{
	printf("\n=== Account Management ===\n");
	printf("%d. Create Another Account\n", CREATE_ACCOUNT_OPTION);
	printf("%d. Delete Account\n", DELETE_ACCOUNT);
	printf("%d. Logout\n", LOGOUT);
	printf("%d. View Balance\n", VIEW_BALANCE);
	printf("%d. Gerer vos comptes\n", MANAGE_ACCOUNTS);
	printf("%d. Save and Exit\n", SAVE_EXIT);
	printf("===========================\n");
	printf("Enter your choice: ");
}

int	find_user(void *data, void *user_id)
{
	if (((t_user *)data)->user_id == (unsigned long long)user_id)
		return (0);
	return (1);
}


int main(void)
{
	t_list				*users;
	t_list				*node;
	e_options			choice;
	unsigned long		index;
	unsigned long long	logged_in;
	FILE				*file;

	srand((unsigned int)time(NULL));
	file = fopen("user_accounts.bin", "rb+");
	if (file == NULL) {
		if ((file = fopen("user_accounts.bin", "wb+")) == NULL)
		{
			perror("Unable to open file for reading/writing");
			return (1);
		}
		users = NULL;
	} else {
		users = deserialize(file);
	}
	choice = INVALID_OPTION;
	logged_in = 0;
	do
	{
		if (logged_in == 0)
		{
			show_main_menu();
			scanf("%d", &choice);
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
					printf("Invalid choice. Please try again.\n");
			}
		}
		else if (choice == MANAGE_ACCOUNTS)
		{
			show_transfer_menu();
			scanf("%d", &choice);
			node = ft_list_find(users, (void *)logged_in, &find_user);
			index = choose_account(((t_user *)node->data));
			switch (choice)
			{
				case DEPOSIT_MONEY:
					depot(((t_user*)node->data), index);
					break;
				case WITHDRAW_MONEY:
					retrait(((t_user*)node->data), index);
					break;
				case TRANSFER_MONEY:
					//					transfer_money();
					break;
				case VIEW_HISTORY:
					print_history(((t_user*)node->data), index);
					break;
				default:
					printf("Invalid option. Please try again.\n");
					break;
			}
		}
		else
		{
			show_acc_man_menu();
			scanf("%d", &choice);
			node = ft_list_find(users, (void *)logged_in, &find_user);
			switch (choice)
			{
				case CREATE_ACCOUNT_OPTION:
					create_account(((t_user *)node->data));
					break;
				case DELETE_ACCOUNT:
					printf("Deleting account (feature coming soon)...\n");
					break;
				case LOGOUT:
					user_logout(&logged_in);
					break;
				case VIEW_BALANCE:
					view_balance(((t_user*)node->data));
					break;
				case MANAGE_ACCOUNTS:
					break;
				case SAVE_EXIT:
					serialize(users, file);
					return (0);
				default:
					printf("Invalid option. Please try again.\n");
					break;
			}
		}
	}
	while (choice != SAVE_EXIT);
	return (1);
}
