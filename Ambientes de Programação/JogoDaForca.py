des_forca = ['''
 +---+
 |   |
     |
     |
     |
     |    
=========''', '''
 +---+
 |   |
 O   |
     |
     |
     |    
=========''', '''
 +---+
 |   |
 O   |
 |   |
     |
     |    
=========''', '''
 +---+
 |   |
 O   |
/|   |
     |
     |    
=========''', '''
 +---+
 |   |
 O   |
/|\  |
     |
     |    
=========''', '''
 +---+
 |   |
 O   |
/|\  |
/    |
     |    
=========''', '''
 +---+
 |   |
 O   |
/|\  |
/ \  |
     |    
=========''']

import random

Animais = ['cachorro', 'galinha', 'porco', 'vaca', 'lagartixa', 'lagosta', 'capivara', 'coruja']
Comidas = ['feijoada', 'sorvete', 'pizza', 'kibe', 'omelete', 'lasanha', 'mingau', 'brigadeiro']
Nomes = ['gustavo', 'aline', 'maria', 'zilda', 'miguel', 'arthur', 'davi', 'gael', 'heitor', 'bernardo']
Frutas = ['banana', 'pera', 'abacaxi', 'acerola', 'figo', 'goiaba', 'jaca', 'kiwi', 'pitaia', 'uva']

print('--------------------------------------------------------------------------')

print('*** Jogo da Forca ***')

print('--------------------------------------------------------------------------')

escolha = int(input("Qual sua escolha ? 1-Animais / 2-Comidas / 3-Nomes / 4-Frutas / 5-Exit : "))

while 1 <= escolha <= 4:

    tentativas = 6
    chute_certo = []
    chute_errado = []
    chutes = []

    if escolha == 1:
        tipo = 'Animal'
        palavra = random.choice(Animais)
    elif escolha == 2:
        tipo = 'Comida'
        palavra = random.choice(Comidas)
    elif escolha == 3:
        tipo = 'Nome'
        palavra = random.choice(Nomes)
    elif escolha == 4:
        tipo = 'Fruta'
        palavra = random.choice(Frutas)

    acertos = ['_'] * len(palavra)

    print('--------------------------------------------------------------------------')

    print(des_forca[tentativas])
    print(' '.join(acertos))
    print('{} com {} letras, Boa Sorte!'.format(tipo, len(palavra)))

    print('--------------------------------------------------------------------------')

    while '_' in acertos and tentativas > 0:

            chute = input("Qual o seu Chute ? ").lower()

            if chute in chutes:
                print("Essa letra já foi chutada! e você perderá uma tentativa!")

                tentativas -= 1

                print("Tentativas restantes: ", tentativas)

                print('--------------------------------------------------------------------------')

            else:

                print('--------------------------------------------------------------------------')

                acertou = False

                for i in range(len(palavra)):
                    if palavra[i] == chute:
                        acertos[i] = chute
                        acertou = True

                if not acertou:
                    tentativas -= 1
                    print(des_forca[tentativas])
                    chute_errado.append(chute)
                    chutes.append(chute)
                else:
                    print(des_forca[tentativas])
                    chute_certo.append(chute)
                    chutes.append(chute)


                print(' '.join(acertos))
                print("Letras certas:", ', '.join(sorted(chute_certo)))
                print("Letras erradas:", ', '.join(sorted(chute_errado)))
                print("Tentativas restantes: ",tentativas)

                print('--------------------------------------------------------------------------')

    print(des_forca[tentativas])

    print('--------------------------------------------------------------------------')

    if tentativas == 0:
        print("Parabéns! infelizmente você não GANHOU a palavra era: ",palavra)
    else:
        print("Parabéns você ganhou!")

    print('--------------------------------------------------------------------------')

    escolha = int(input("Jogar Novamente ? 1-Animais / 2-Comidas / 3-Nomes / 4-Frutas / 5-Exit : "))





