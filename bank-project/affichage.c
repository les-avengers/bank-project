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
/*   affichage.c                                   |__ --==|'-''' '...;       */
/*                                                [  ]  :[|       |---\       */
/*   By: smail <smailnice06@icloud.com>           |__| I=[|     .'    '.      */
/*                                                / / ____|     :       '._   */
/*   Created: 2024/10/17 14:51:02 by smail       |-/.____.'      | :      :   */
/*   Updated: 2024/10/17 16:15:27 by smail        /___ /___      '-'._----'   */
/*                                                                            */
/* ************************************************************************** */


#include "bank_ops.h"


void menu(t_user *user){
    int numberofcase;
    
    
    printf("\n menu:\n");
    printf("- 0:Quitter\n");
    printf("- 1:Check account\n");
    printf("- 2:Acceder aux parametres\n");
    printf("- 3:Faire un depot\n");
    printf("- 4:Faire un retrait\n");
    printf("- 5:Faire un virement\n");
    printf("Veuillez saisir un de ces chiffres: ");
    
    scanf("%d", &numberofcase);
    
    
    
    switch (numberofcase) {
        case 0:
            break;
        
        case 1:
            voir_balance(user);
            menu(user);
            break;
        
        case 2:
            parametres(user);
            menu(user);
            break;
        
        case 3:
            depot(user);
            menu(user);
            break;
        
        case 4:
            retrait(user);
            menu(user);
            break;
            
        default:
            printf("Nous somme désolé mais cet opération n'existe pas\n");
            menu(user);
            break;
    }
    
    
    
    
    
}


void parametres(t_user *user){
    int numberofcase;
    
    
    printf("\n Paramètres:\n");
    printf("- 1:Afficher votre numero de compte\n");
    printf("- 2:Modifier votre numero de compte\n");
    printf("- 3:Afficher votre mot de passe\n");
    printf("- 4:Modifier votre mot de passe\n");
    printf("- 5:Revenir au prècedent menu\n");
    printf("Veuillez saisir un de ces chiffres: ");

    
    scanf("%d", &numberofcase);
    
    switch (numberofcase) {
        case 1:
            afficher_user(user);
            parametres(user);
            break;
        
        case 2:
            modify_nameuser(user);
            parametres(user);
            break;
        
        case 3:
            afficher_password(user);
            parametres(user);
            break;
            
            
        case 4:
            modify_password(user);
            parametres(user);
            break;
            
        case 5:
            menu(user);
            break;
            
            
        default:
            printf("Nous somme désolé mais cet opération n'existe pas");
            parametres(user);
            break;
    }

    
    
    
}


