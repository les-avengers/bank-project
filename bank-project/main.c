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

//t_user	*populate_user(char *username, char *password,
//					   unsigned long balance)
//{
//	t_user	*user;
//
//	user = NULL;
//	if ((user = (t_user *)malloc(sizeof(t_user))))
//	{
//		user->username = username;
//		user->password = password;
//		user->balance = balance;
//	}
//	return (user);
//}

void	show_menu(bool logged_in)
{
	printf("\n=== Banking System Menu ===\n");
	if (!logged_in)
	{
		printf("1. Login\n");
		printf("2. Create Account\n");
		printf("9. Save and Exit\n");
	}
	else
	{
		printf("3. Logout\n");
		printf("4. View Account Balance\n");
		printf("5. Deposit Money\n");
		printf("6. Withdraw Money\n");
		printf("7. Transfer Money\n");
		printf("8. View Transaction History\n");
		printf("9. Save and Exit\n");
	}
	printf("===========================\n");
	printf("Enter your choice: ");
}

int main(void)
{
	t_list *head = NULL;
	t_account *account1 = (t_account *)malloc(sizeof(t_account));
	account1->acc_no = 101;
	account1->balance = 1000.0;
	account1->type = strdup("Savings");
	account1->next = NULL;
	
	t_account *account2 = (t_account *)malloc(sizeof(t_account));
	account2->acc_no = 102;
	account2->balance = 5000.0;
	account2->type = strdup("Investment");
	account2->next = NULL;
	account1->next = account2;
	
	t_account *account3 = (t_account *)malloc(sizeof(t_account));
	account3->acc_no = 103;
	account3->balance = 1000.0;
	account3->type = strdup("TJ acc");
	account3->next = NULL;
	account2->next = account3;
	
	t_user user1 = {
		strdup("Alice"),
		strdup("Smith"),
		strdup("password123"),
		1234567890,
		10000,
		account1,
		3
	};
	ft_list_push_front(&head, &user1);
	
	t_user user2 = {
		strdup("John"),         // prénom
		strdup("Smith"),         // nom
		strdup("passwrd123"),   // mots_de_passe
		1234567890,              // numéro_de_téléphone
		10000,                   // balance
		account2,                // accounts
		2
	};
	ft_list_push_front(&head, &user2);
	FILE *file = fopen("user_accounts.bin", "wb");
	if (file == NULL)
	{
		perror("Unable to open file for writing");
		return (1);
	}
	serialize(head, file);
	fclose(file);
	printf("===============SERIALIZED DATA===============\n");
	t_list *current = head;
	while (current != NULL) {
		t_user *user = (t_user *)current->data;
		printf("User: %s %s\n", user->prénom, user->nom);
		t_account *acc = user->accounts;
		while (acc != NULL) {
			printf("Account: %lu, Type: %s, Balance: %.2f\n", acc->acc_no, acc->type, acc->balance);
			acc = acc->next;
		}
		current = current->next;
	}
	current = NULL;
	printf("=============DESERIALIZED DATA===============\n");
	ft_list_clear(head, free);
	file = fopen("user_accounts.bin", "rb");
	if (file == NULL)
	{
		perror("Unable to open file for reading");
		return 1;
	}
	t_list *deserialized_head = deserialize(file);
	fclose(file);
	current = deserialized_head;
	while (current != NULL)
	{
		t_user *user = (t_user *)current->data;
		printf("User: %s %s\n", user->prénom, user->nom);
		t_account *acc = user->accounts;
		while (acc != NULL)
		{
			printf("Account: %lu, Type: %s, Balance: %.2f\n", acc->acc_no, acc->type, acc->balance);
			acc = acc->next;
		}
		current = current->next;
	}
	ft_list_clear(deserialized_head, free);
	return (0);
}


//int main(void)
//{
//	t_list	**users;
//	short	choice;
//	bool	logged_in;
//
//	users = NULL;
//	choice = -1;
//	logged_in = 0;
//	users = malloc(sizeof(t_list *));
//	do
//	{
//		show_menu(logged_in);
//		scanf("%hd", &choice);
//		switch (choice) {
//			case 1:
//				printf("Pass\n");
//				break;
//				
//			default:
//				break;
//		}
//	}
//	while (choice != 9);
//	return (0);
//}
