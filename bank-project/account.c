//
//  account.c
//  bank-project
//
//  Created by Teghjyot Singh on 12/11/2024.
//

#include "account.h"

void	show_account_menu(void)
{
	printf("\n===================================\n");
	printf("\t=== Choisissez le type de compte ===\n");
	printf("===================================\n");
	printf("%d. Compte courant\n", COMPTE_COURANT);
	printf("%d. Livret d'épargne\n", LIVRET_EPARGNE);
	printf("===============================\n");
	printf("Entrez votre choix : ");
}

int	calculate_check_digits(const char* iban)
{
	char			temp[100];
	size_t			i;
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
			printf("Aucun compte n'a été créé\n");
			return;
	}
	generate_iban(account);
	user->num_accounts += 1;
	account->creation_time = time(NULL);
	ft_list_push_front(accounts, account);
	printf("\nCompte créé avec succès !\n");
	printf("===================================\n");
}

void	display_accounts(t_user *user) {
	t_list 		*current_account;
	t_account	*account;
	size_t		i;
	
	if (user == NULL)
	{
		printf("Utilisateur invalide.\n");
		return;
	}
	if (user->num_accounts > 0)
	{
		printf("Vous avez %zu compte(s) :\n", user->num_accounts);
		current_account = user->accounts;
		i = 0;
		while (current_account != NULL)
		{
			account = (t_account *)current_account->data;
			printf("Compte #%zu :\n", i + 1);
			printf("\tNuméro de compte : %lu\n", account->acc_no);
			printf("\tType de compte : ");
			switch (account->type)
			{
				case COMPTE_COURANT:
					printf("Compte courant\n");
					break;
				case LIVRET_EPARGNE:
					printf("Compte d'épargne\n");
					break;
				default:
					printf("Type inconnu\n");
					break;
			}
			printf("\tSolde : %.2f\n", account->balance);
			printf("\tIBAN : %s\n", account->iban);
			printf("\tCréé le : %s", ctime(&account->creation_time));
			current_account = current_account->next;
			i++;
		}
	}
	printf("Aucun compte n'a été créé pour l'instant.\n");
}

void apply_interest(t_account *compte, double rate, bool silence)
{
	double	minute_diff;
	double	period;
	double	final;
	double	interet;
	
	if (compte->type == LIVRET_EPARGNE)
	{
		minute_diff = difftime(time(NULL), compte->creation_time) / 60.0;
		period = 60 * 24 * 365;
		final = compte->balance * pow(1 + rate / period, minute_diff);
		interet = final - compte->balance;
		compte->balance = final;
		if (!silence)
		{
			printf("\n===================================\n");
			printf("Intérêt appliqué: %.2f EUR\n", interet);
			printf("Nouveau solde: %.2f EUR\n", compte->balance);
			printf("===================================\n");
		}
		
	}
}

void	view_balance(t_user *user) {
	t_list *current_account;
	t_account *account;
	size_t i;
	double total;
	
	if (user == NULL) {
		printf("Utilisateur invalide.\n");
		return;
	}
	current_account = user->accounts;
	i = 0;
	total = 0;
	printf("\n===================================\n");
	printf("        Solde des comptes        \n");
	printf("===================================\n");
	while (current_account != NULL) {
		account = (t_account *)current_account->data;
		printf("\nCompte #%zu:\n", i + 1);
		printf("\tIBAN: %s\n", account->iban);
		printf("\tType de compte: ");
		switch (account->type) {
			case COMPTE_COURANT:
				printf("Compte courant\n");
				break;
			case LIVRET_EPARGNE:
				printf("Livret d'épargne\n");
				apply_interest(account, M_PI, false);
				break;
			default:
				printf("Type inconnu\n");
				break;
		}
		total += account->balance;
		printf("\tSolde: %.2f EUR\n", account->balance);
		current_account = current_account->next;
		i++;
	}
	printf("===================================\n");
	printf("SOLDE TOTAL: %.2f EUR\n", total);
	printf("===================================\n");
}

unsigned long	choose_account(t_user *user) {
	t_list		*current_account;
	t_account	*account;
	size_t		i;
	
	current_account = user->accounts;
	i = 0;
	if (current_account == NULL)
	{
		printf("Aucun compte trouvé pour cet utilisateur.\n");
		return -1;
	}
	printf("\nVeuillez choisir un compte parmi ceux-ci:\n");
	printf("===================================\n");
	while (current_account != NULL)
	{
		account = (t_account *)current_account->data;
		printf("Compte #%zu :\n", i + 1);
		printf("\tIBAN : %s\n", account->iban);
		printf("\tType de compte : ");
		switch (account->type) {
			case COMPTE_COURANT:
				printf("Compte courant\n");
				break;
			case LIVRET_EPARGNE:
				printf("Livret d'épargne\n");
				apply_interest(account, M_PI, true);
				break;
			default:
				printf("Type inconnu\n");
				break;
		}
		printf("\tSolde : %.2f EUR\n", account->balance);
		current_account = current_account->next;
		i++;
	}
	printf("\nVeuillez choisir votre compte en indiquant le numéro : ");
	scanf("%zu", &i);
	if (i == 0 || i > user->num_accounts)
	{
		printf("Numéro de compte invalide. Veuillez réessayer.\n");
		return -1;
	}
	return (i - 1);
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
		perror("Erreur lors de l'ouverture du fichier");
		return;
	}
	fprintf(file, "%s : %f, Nouveau solde : %f\n", transaction, amount, balance);
	fclose(file);
	printf("Transaction enregistrée dans l'historique.\n");
}

void depot(t_user **user, unsigned long i) {
	size_t		account_count;
	double		balance;
	t_account	*account;

	if (*user == NULL || (*user)->accounts == NULL)
	{
		printf("L'utilisateur ou ses comptes sont NULL.\n");
		return;
	}
	account_count = ft_list_size((*user)->accounts);
	if (i >= account_count)
	{
		printf("Index de compte invalide.\n");
		return;
	}
	printf("\nEntrez le montant à déposer (en EUR): ");
	if (scanf("%lf", &balance) != 1 || balance <= 0)
	{
		printf("Entrée invalide pour le solde. Veuillez entrer un montant positif.\n");
		return;
	}
	account = ft_list_at((*user)->accounts, (unsigned int)i)->data;
	apply_interest(account, M_PI, true);
	account->balance += balance;
	log_transaction(account->iban, "Dépôt", balance, account->balance);
	printf("\n===================================\n");
	printf("Dépôt effectué avec succès!\n");
	printf("Nouveau solde: %.2f EUR\n", account->balance);
	printf("===================================\n");
}

void	retrait(t_user **user, unsigned long i) {
	double		balance;
	t_account	*account;
	
	printf("\nEntrez le montant à retirer (en EUR): ");
	if (scanf("%lf", &balance) != 1 || balance <= 0)
	{
		printf("Entrée invalide pour le solde. Veuillez entrer un montant positif.\n");
		return;
	}
	account = ft_list_at((*user)->accounts, (unsigned int)i)->data;
	apply_interest(account, M_PI, true);
	if (account->balance - balance < 0) {
		printf("Fonds insuffisants!\n");
	}
	else
	{
		account->balance -= balance;
		log_transaction(account->iban, "Retrait", balance, account->balance);
		printf("\n===================================\n");
		printf("Retrait effectué avec succès!\n");
		printf("Nouveau solde: %.2f EUR\n", account->balance);
		printf("===================================\n");
	}
}

t_account	*search_iban(t_list *users, char *iban)
{
	t_list		*current;
	t_user		*user;
	t_list		*current_acc;
	t_account	*account;

	current = users;
	while (current != NULL)
	{
		user = (t_user *)current->data;
		current_acc = user->accounts;
		while (current_acc != NULL)
		{
			account = (t_account *)current_acc->data;
			if (strncmp(iban, account->iban, 32) == 0)
				return (account);
			current_acc = current_acc->next;
		}
		current = current->next;
	}
	return (NULL);
}

void	transfer(t_list *users, t_user **user, unsigned long i)
{
	double		balance;
	t_account	*source_account;
	t_account	*destination_account;
	char		iban_dest[34];
	t_list		*current_user_node;
	t_user		*current_user;
	t_list		*current_account_node;
	
	destination_account = NULL;
	printf("\nEntrez l'IBAN du destinataire: ");
	if (scanf("%s", iban_dest) != 1)
	{
		printf("Erreur de lecture de l'IBAN du destinataire.\n");
		return;
	}
	printf("\nEntrez le montant à transférer (en EUR): ");
	if (scanf("%lf", &balance) != 1 || balance <= 0)
	{
		printf("Entrée invalide pour le montant du transfert.\n");
		return;
	}
	source_account = ft_list_at((*user)->accounts, (unsigned int)i)->data;
	apply_interest(source_account, M_PI, true);
	if (source_account->balance - balance < 0)
	{
		printf("Fonds insuffisants!\n");
		return;
	}
	current_user_node = users;
	while (current_user_node != NULL)
	{
		current_user = (t_user *)current_user_node->data;
		current_account_node = current_user->accounts;
		while (current_account_node != NULL)
		{
			t_account *account = (t_account *)current_account_node->data;
			
			if (strcmp(account->iban, iban_dest) == 0)
			{
				destination_account = account;
				break;
			}
			current_account_node = current_account_node->next;
		}
		if (destination_account != NULL)
			break;
		current_user_node = current_user_node->next;
	}
	if (destination_account == NULL)
	{
		printf("IBAN du destinataire introuvable.\n");
		return;
	}
	source_account->balance -= balance;
	destination_account->balance += balance;
	log_transaction(source_account->iban, "Virement envoyé", balance, source_account->balance);
	log_transaction(destination_account->iban, "Virement reçu", balance, destination_account->balance);
	printf("\n===================================\n");
	printf("Virement effectué avec succès!\n");
	printf("Votre nouveau solde: %.2f EUR\n", source_account->balance);
	printf("Solde du destinataire: %.2f EUR\n", destination_account->balance);
	printf("===================================\n");
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
		perror("Erreur lors de l'ouverture du fichier");
		return;
	}
	printf("\nHistorique des transactions pour le compte IBAN: %s\n", account->iban);
	printf("===================================\n");
	while ((c = fgetc(file)) != EOF)
		putchar(c);
	printf("\n===================================\n");
	fclose(file);
}

void	delete_account(t_user **user, unsigned long i)
{
	t_account	*account;
	t_list		*node;

	node = ft_list_at((*user)->accounts, (unsigned int)i);
	if (!node || !node->data)
		return;
	account = (t_account *)node->data;
	if (account->iban)
	{
		free(account->iban);
		account->iban = NULL;
	}
	free(account);
	ft_list_delete_node(&(*user)->accounts, node, free);
}
