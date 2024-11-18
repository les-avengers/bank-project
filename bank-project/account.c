//
//  account.c
//  bank-project
//
//  Created by Teghjyot Singh on 12/11/2024.
//

#include "account.h"

void	show_account_menu(void)
{
	printf("\n=== Choose Account Type ===\n");
	printf("%d. Compte courant\n", COMPTE_COURANT);
	printf("%d. Livret d'épargne\n", LIVRET_EPARGNE);
	printf("===========================\n");
	printf("Enter your choice: ");
}

int	calculate_check_digits(const char* iban)
{
	char			temp[100];
	int				i;
	long long int	number;
	long long int	check_digits;

	i = 0;
	snprintf(temp, sizeof(temp), "%s", iban + 4);
	number = 0;
	while (i < strlen(temp))
		number = number * 10 + (temp[i++] - '0');
	check_digits = number % 97;
	return (98 - check_digits) % 97;
}


long long int	generate_account_number(void)
{
	static long long int	counter;
	long long int			timestamp;
	long long int			id;
	
	timestamp = (long long )time(NULL);
	if (timestamp % 1000 == 0)
		counter = 0;
	id = (timestamp << 16) | (counter++);
	return (id);
}

void generate_iban(t_account *account)
{
	int				check_digits;
	char			account_str[20];
	long long int	account_number;
	const char		*bank_code;

	bank_code = "9999";
	account_number = generate_account_number();
	account->acc_no = account_number;
	account->iban = (char *)malloc((34 + 1) * sizeof(char));
	bzero(account_str, sizeof(account_str));
	snprintf(account_str, sizeof(account_str), "%lld", account_number);
	while (strlen(account_str) < 12)
	{
		memmove(account_str + 1, account_str, strlen(account_str) + 1);
		account_str[0] = '0';
	}
	snprintf(account->iban, 34, "%s00%s%s", "FR", bank_code, account_str);
	check_digits = calculate_check_digits(account->iban);
	snprintf(account->iban, 34, "%s%02d%s%s", "FR", check_digits, bank_code, account_str);
}

void	create_account(t_user *user)
{
	t_list		**accounts;
	t_account	*account;
	int			type;

	accounts = &user->accounts;
	account = (t_account *)malloc(sizeof(t_account));
	account->balance = 0;
	show_account_menu();
	scanf("%d", &type);
	switch (type) {
		case COMPTE_COURANT:
			account->type = COMPTE_COURANT;
			break;
		case LIVRET_EPARGNE:
			account->type = LIVRET_EPARGNE;
			break;
		default:
			free(account);
			printf("No account was created\n");
			return;
	}
	generate_iban(account);
	user->num_accounts += 1;
	account->creation_time = time(NULL);
	ft_list_push_front(accounts, account);
}

void	display_accounts(t_user *user) {
	t_list 		*current_account;
	t_account	*account;
	size_t		i;

	if (user == NULL)
	{
		printf("Invalid user.\n");
		return;
	}
	if (user->num_accounts > 0)
	{
		printf("You have %zu account(s):\n", user->num_accounts);
		current_account = user->accounts;
		i = 0;
		while (current_account != NULL)
		{
			account = (t_account *)current_account->data;
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
			i++;
		}
	}
		printf("No accounts have been created yet.\n");
}

void apply_interest(t_account *compte, double rate, bool silence)
{
	double	minute_diff;
	double	period;
	double	final;
	double	interet;

	minute_diff = difftime(time(NULL), compte->creation_time) / 60.0;
	period = 60 * 24 * 365;
	final = compte->balance * pow(1 + rate / period, minute_diff);
	interet = final - compte->balance;
	compte->balance = final;
	if (!silence)
	{
		printf("Intérêt composé appliqué: %.2f EUR\n", interet);
		printf("Nouveau solde: %.2f EUR\n", compte->balance);
	}
}

void	view_balance(t_user *user)
{
	t_list 		*current_account;
	t_account	*account;
	size_t		i;
	double		total;

	if (user == NULL)
	{
		printf("Invalid user.\n");
		return;
	}
	current_account = user->accounts;
	i = 0;
	total = 0;
	while (current_account != NULL)
	{
		account = (t_account *)current_account->data;
		printf("Account #%zu:\n", i + 1);
		printf("\tIBAN: %s\n", account->iban);
		printf("\tAccount Type: ");
		switch (account->type)
		{
			case COMPTE_COURANT:
				printf("Compte courant\n");
				break;
			case LIVRET_EPARGNE:
				printf("Livret d'épargne\n");
				apply_interest(account, M_PI, false);
				break;
			default:
				printf("Type inconnue\n");
				break;
		}
		total += account->balance;
		printf("\tBalance: %.2f\n", account->balance);
		current_account = current_account->next;
		i++;
	}
	printf("===================================\n");
	printf("\tSOLDE TOTALE: %lf\n", total);
	printf("===================================\n");
}

unsigned long	choose_account(t_user *user)
{
	t_list 		*current_account;
	t_account	*account;
	size_t		i;

	current_account = user->accounts;
	i = 0;
	while (current_account != NULL)
	{
		account = (t_account *)current_account->data;
		printf("Account #%zu:\n", i + 1);
		printf("\tIBAN: %s\n", account->iban);
		printf("\tAccount Type: ");
		switch (account->type)
		{
			case COMPTE_COURANT:
				printf("Compte courant\n");
				break;
			case LIVRET_EPARGNE:
				printf("Livret d'épargne\n");
				apply_interest(account, M_PI, true);
				break;
			default:
				printf("Type inconnue\n");
				break;
		}
		printf("\tBalance: %.2f\n", account->balance);
		current_account = current_account->next;
	}
	printf("Veillez choisir votre compte #: ");
	scanf("%zd", &i);
	i--;
	return (i);
}

void	log_transaction(const char *iban, const char *transaction,
						double amount, double balance)
{
	char	filename[50];
	FILE	*file;

	system("mkdir -p history");
	snprintf(filename, sizeof(filename), "history/%s.txt", iban);
	file = fopen(filename, "a");
	if (file == NULL)
	{
		perror("Error opening file");
		return;
	}
	fprintf(file, "%s: %f, New Balance: %f\n", transaction, amount, balance);
	fclose(file);
}

void    depot(t_user *user, unsigned long i)
{
	double			balance;
	t_account		*account;

	printf("Choose amount to deposit: ");
	scanf("%lf", &balance);
	account = ft_list_at(user->accounts, (unsigned int)i)->data;
	account->balance += balance;
	log_transaction(account->iban, "Depot", balance, account->balance);
}

void    retrait(t_user *user, unsigned long i)
{
	double			balance;
	t_account		*account;

	printf("Choose amount to withdraw: ");
	scanf("%lf", &balance);
	account = ft_list_at(user->accounts, (unsigned int)i)->data;
	if (account->balance - balance < 0)
		printf("Insufficient funds!");
	else
		account->balance -= balance;
	log_transaction(account->iban, "Retrait", balance, account->balance);
}

void	print_history(t_user *user, unsigned long i)
{
	t_account		*account;
	FILE			*file;
	char			c;
	char			filename[50];

	account = ft_list_at(user->accounts, (unsigned int)i)->data;
	system("mkdir -p history");
	snprintf(filename, sizeof(filename), "history/%s.txt", account->iban);
	file = fopen(filename, "r");
	if (file == NULL)
	{
		perror("Error opening file");
		return;
	}
	while ((c = fgetc(file)) != EOF)
		putchar(c);
	fclose(file);
}
