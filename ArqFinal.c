#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define ArqPessoa "pessoa.txt"
#define ArqEmail "email.txt"
#define ArqTelefone "telefone.txt"

typedef struct email //struct para cadastro de email
{
  int Id;
  int Idhumano;
  char email[255];
} Email;

typedef struct Num //struct para cadastro do numero de telefone
{
  int id;
  int Idhumano;
  char Telefone[12];
} Telefone;

typedef struct Pessoa //struct para cadastro de nome
{
  int id;
  char Nome[55];
} CadPessoa;

typedef struct dados //struct para juntar todos os dados
{
  CadPessoa *Humano;
  Email *emails;
  Telefone *telefones;
  int PessoaTam;
  int EmailTam;
  int TelefoneTam;
  int LasPessoaId;
  int LasTelefoneId;
  int LasEmailId;
} CadastroPessoa;

void writeToFile(CadastroPessoa *_data); // escrever e salvar os arquivos
CadastroPessoa loadFromFile();

void ExibirTudo(CadastroPessoa *_data);
void ExibirPessoa(CadastroPessoa *_data, int _id);
void InserirPessoa(CadastroPessoa *_data, char *_name);
void InserirTelefone(CadastroPessoa *_data, Telefone *_telephone);
void AdcEmail(CadastroPessoa *_data, Email *_email);
void ModPessoa(CadastroPessoa *_data, CadPessoa *_person);
void ModTelefone(CadastroPessoa *_data, Telefone *_telephone);
void ModEmail(CadastroPessoa *_data, Email *_email);
void ExcluirPessoa(CadastroPessoa *_data, int _id);
void ExcluirTelefone(CadastroPessoa *_data, int _id);
void ExcluirEmail(CadastroPessoa *_data, int _id);
void ExibirMenu();

int main(int argc, char const *argv[])
{
  CadastroPessoa dados = loadFromFile();

  int response;

  do //Exibir o menu  e opções selecionadas
  {
    ExibirMenu();
    scanf("%d", &response);

    switch (response)
    {
    case 1:
    {
      ExibirTudo(&dados);
      break;
    }

    case 2:
    {
      int id;
      printf("Insira o id da pessoa:\n");
      scanf("%d", &id);

      ExibirPessoa(&dados, id);

      break;
    }

    case 3:
    {
      char Nome[55];
      printf("Insira o nome da pessoa:\n");
      scanf("%s", Nome);

      InserirPessoa(&dados, Nome);
      break;
    }

    case 4:
    {
      Telefone Num;

      printf("Insira o id da pessoa para adcionar este telefone:\n");
      scanf("%d", &Num.Idhumano);
      printf("Insira o telefone:\n");
      scanf("%s", Num.Telefone);

      InserirTelefone(&dados, &Num);
      break;
    }

    case 5:
    {
      Email email;

      printf("Insira o id da pessoa para adcionar este email:\n");
      scanf("%d", &email.Idhumano);
      printf("Insira o email:\n");
      scanf("%s", email.email);

      AdcEmail(&dados, &email);
      break;
    }

    case 6:
    {
      CadPessoa Pessoa;

      printf("Insira o id da pessoa para alterar:\n");
      scanf("%d", &Pessoa.id);
      printf("Insira o nome da pessoa ou deixe vazio para não alterar:\n");
      scanf("%s", Pessoa.Nome);

      ModPessoa(&dados, &Pessoa);
      break;
    }

    case 7:
    {
      Telefone t;
      printf("Insira o id do telefone que deseja alterar:\n");
      scanf("%d", &t.id);
      printf("Insira o id da pessoa (caso queira adcionar a outra pessoa este telefone, senão insira -1):\n");
      scanf("%d", &t.Idhumano);
      printf("Insira o telefone:\n");
      scanf("%s", t.Telefone);

      ModTelefone(&dados, &t);
      break;
    }

    case 8:
    {
      Email e;
      printf("Insira o id do email que deseja alterar:\n");
      scanf("%d", &e.Id);
      printf("Insira o id da pessoa (caso queira atribuir a outra pessoa este email, senão insira -1):\n");
      scanf("%d", &e.Idhumano);
      printf("Insira o email:\n");
      scanf("%s", e.email);

      ModEmail(&dados, &e);
      break;
    }

    case 9:
    {
      int id;
      printf("Insira o id da pessoa que deseja excluir:\n");
      scanf("%d", &id);

      ExcluirPessoa(&dados, id);

      break;
    }

    case 10:
    {
      int id;
      printf("Insira o id do telefone que deseja excluir:\n");
      scanf("%d", &id);

      ExcluirTelefone(&dados, id);

      break;
    }

    case 11:
    {
      int id;
      printf("Insira o id do email que deseja excluir:\n");
      scanf("%d", &id);

      ExcluirEmail(&dados, id);

      break;
    }

    default:
      break;
    }
  } while (response != 0);

  writeToFile(&dados); //escrever e salvar o arquivo

  return 0;
}

void ExibirMenu()
{
  printf("Escolha uma opção:\n");
  printf("\t0 - Sair\n");
  printf("\t1 - Exibir todos contatos\n");
  printf("\t2 - Exibir contato\n");
  printf("\t3 - Inserir contato\n");
  printf("\t4 - Inserir telefone\n");
  printf("\t5 - Inserir Email\n");
  printf("\t6 - Editar Pessoa\n");
  printf("\t7 - Editar Telefone\n");
  printf("\t8 - Editar Email\n");
  printf("\t9 - Excluir Pessoa\n");
  printf("\t10 - Excluir Telefone\n");
  printf("\t11 - Excluir Email\n");
}

CadastroPessoa loadFromFile()
{
  FILE *PessoaTXT = fopen(ArqPessoa, "r");
  FILE *TelefoneTXT = fopen(ArqTelefone, "r");
  FILE *emailTXT = fopen(ArqEmail, "r");

  CadastroPessoa DataPessoa;

  DataPessoa.PessoaTam = 0;
  DataPessoa.EmailTam = 0;
  DataPessoa.TelefoneTam = 0; // contadores de cadastro
  DataPessoa.LasPessoaId = 0;
  DataPessoa.LasTelefoneId = 0;
  DataPessoa.LasEmailId = 0; // contador do ultimo id
  DataPessoa.Humano = malloc(sizeof(CadPessoa));
  DataPessoa.emails = malloc(sizeof(Email));
  DataPessoa.telefones = malloc(sizeof(Telefone)); // alocar dinamicamente a variaveis

  if (ArqPessoa == NULL || ArqTelefone == NULL || ArqEmail == NULL) // função pra arquivo não criado
  {
    printf("*** O arquivo não existe, ele será criado no final da execução do programa\n\n");
  }
  else
  {
    CadPessoa Pessoa;
    memset(&Pessoa, 0, sizeof(CadPessoa));

    while (fscanf(PessoaTXT, "%d;%[^\n]\n", &Pessoa.id, Pessoa.Nome) != EOF) // imprimir a variavel
    {
      DataPessoa.LasPessoaId = Pessoa.id;
      DataPessoa.Humano[DataPessoa.PessoaTam] = Pessoa;

      DataPessoa.PessoaTam++;

      if (!feof(PessoaTXT))
      {
        DataPessoa.Humano = realloc(DataPessoa.Humano, sizeof(CadPessoa) * (DataPessoa.PessoaTam + 1));
        memset(&Pessoa, 0, sizeof(CadPessoa));
      }
    }

    Telefone Num;

    while (fscanf(TelefoneTXT, "%d;%d;%[^\n]\n", &Num.id, &Num.Idhumano, Num.Telefone) != EOF)
    {
      DataPessoa.LasTelefoneId = Num.id;
      DataPessoa.telefones[DataPessoa.TelefoneTam] = Num;

      DataPessoa.TelefoneTam++;

      if (!feof(TelefoneTXT))
      {
        DataPessoa.telefones = realloc(DataPessoa.telefones, sizeof(Telefone) * (DataPessoa.TelefoneTam + 1));
        memset(&Num, 0, sizeof(Telefone));
      }
    }

    Email email;

    while (fscanf(emailTXT, "%d;%d;%[^\n]\n", &email.Id, &email.Idhumano, email.email) != EOF)
    {
      DataPessoa.LasEmailId = email.Id;
      DataPessoa.emails[DataPessoa.EmailTam] = email;

      DataPessoa.EmailTam++;

      if (!feof(emailTXT))
      {
        DataPessoa.emails = realloc(DataPessoa.emails, sizeof(Email) * (DataPessoa.EmailTam + 1));
        memset(&email, 0, sizeof(Email));
      }
    }

    fclose(PessoaTXT); //fechar e 
    fclose(TelefoneTXT);
    fclose(emailTXT);
  }

  return DataPessoa; //retornar o arquivo de dados
}

void writeToFile(CadastroPessoa *_data)
{
  FILE *PessoaTXT = fopen(ArqPessoa, "w");
  FILE *TelefoneTXT = fopen(ArqTelefone, "w");
  FILE *emailTXT = fopen(ArqEmail, "w");

  if (PessoaTXT == NULL || TelefoneTXT == NULL || emailTXT == NULL)
  {
    printf("Não foi possivel escrever nos arquivos!\n");
    exit(1);
  }

  for (size_t i = 0; i < _data->PessoaTam; i++)
  {
    fprintf(PessoaTXT, "%d;%s\n", _data->Humano[i].id, _data->Humano[i].Nome);
  }

  for (size_t i = 0; i < _data->TelefoneTam; i++)
  {
    fprintf(TelefoneTXT, "%d;%d;%s\n", _data->telefones[i].id, _data->telefones[i].Idhumano, _data->telefones[i].Telefone);
  }

  for (size_t i = 0; i < _data->EmailTam; i++)
  {
    fprintf(emailTXT, "%d;%d;%s\n", _data->emails[i].Id, _data->emails[i].Idhumano, _data->emails[i].email);
  }

  fclose(PessoaTXT);
  fclose(TelefoneTXT);
  fclose(emailTXT);
}


void ExibirTudo(CadastroPessoa *_data) //exibe todos os dados
{
  for (size_t i = 0; i < _data->PessoaTam; i++)
  {
    int Idhumano = _data->Humano[i].id;

    printf("Pessoa %d:\n", _data->Humano[i].id);
    printf("\tNome: %s\n", _data->Humano[i].Nome);
    printf("\tTelefones:\n");

    for (size_t j = 0; j < _data->TelefoneTam; j++)
    {
      if (_data->telefones[j].Idhumano == Idhumano)
      {
        printf("\t\tTelefone %d: %s\n", _data->telefones[j].id, _data->telefones[j].Telefone);
      }
    }

    printf("\tEmails:\n");

    for (size_t j = 0; j < _data->TelefoneTam; j++)
    {
      if (_data->emails[j].Idhumano == Idhumano)
      {
        printf("\t\tEmail %d: %s\n", _data->emails[j].Id, _data->emails[j].email);
      }
    }
    printf("\n\n");
  }
}

void ExibirPessoa(CadastroPessoa *_data, int _id) // exibe apenas uma pessoa selecionada p id
{
  for (size_t i = 0; i < _data->PessoaTam; i++)
  {
    if (_data->Humano[i].id == _id)
    {
      printf("Pessoa %d:\n", _data->Humano[i].id);
      printf("\tNome: %s\n", _data->Humano[i].Nome);
      printf("\tTelefones:\n");

      for (size_t j = 0; j < _data->TelefoneTam; j++)
      {
        if (_data->telefones[j].Idhumano == _data->Humano[i].id)
        {
          printf("\t\tTelefone %d: %s\n", _data->telefones[j].id, _data->telefones[j].Telefone);
        }
      }

      printf("\tEmails:\n");

      for (size_t j = 0; j < _data->TelefoneTam; j++)
      {
        if (_data->emails[j].Idhumano == _data->Humano[i].id)
        {
          printf("\t\tEmail %d: %s\n", _data->emails[j].Id, _data->emails[j].email);
        }
      }

      return;
    }
  }

  printf("Id não encontrado!\n");
}

void InserirPessoa(CadastroPessoa *_data, char *_name)
{
  _data->Humano = realloc(_data->Humano, sizeof(CadPessoa) * (_data->PessoaTam + 1));
  _data->Humano[_data->PessoaTam].id = ++_data->LasPessoaId;

  strcpy(_data->Humano[_data->PessoaTam].Nome, _name);

  _data->PessoaTam++;
}

int personExists(CadastroPessoa *_data, int _id)
{
  for (size_t i = 0; i < _data->PessoaTam; i++)
    if (_data->Humano[i].id == _id)
      return TRUE;

  return FALSE;
}

void InserirTelefone(CadastroPessoa *_data, Telefone *_telephone)
{
  if (!personExists(_data, _telephone->Idhumano))
  {
    printf("O id inserido para adcionar este telefone não existe\n");
    return;
  }

  _data->telefones = realloc(_data->telefones, sizeof(Telefone) * (_data->TelefoneTam + 1));
  _data->telefones[_data->TelefoneTam].id = ++_data->LasTelefoneId;

  _data->telefones[_data->TelefoneTam].Idhumano = _telephone->Idhumano;
  strcpy(_data->telefones[_data->TelefoneTam].Telefone, _telephone->Telefone);

  _data->TelefoneTam++;
}

void AdcEmail(CadastroPessoa *_data, Email *_email)
{
  if (!personExists(_data, _email->Idhumano))
  {
    printf("O id inserido para adcionar este email não existe\n");
    return;
  }

  _data->emails = realloc(_data->emails, sizeof(Email) * (_data->EmailTam + 1));
  _data->emails[_data->EmailTam].Id = ++_data->LasEmailId;

  _data->emails[_data->EmailTam].Idhumano = _email->Idhumano;
  strcpy(_data->emails[_data->EmailTam].email, _email->email);

  _data->EmailTam++;
}

void ModPessoa(CadastroPessoa *_data, CadPessoa *_person)
{
  for (size_t i = 0; i < _data->PessoaTam; i++)
  {
    if (_data->Humano[i].id == _person->id)
    {
      if (strlen(_person->Nome) > 0)
      {
        strcpy(_data->Humano[i].Nome, _person->Nome);
      }

      return;
    }
  }

  printf("Id não encontrado!\n");
}

void ModTelefone(CadastroPessoa *_data, Telefone *_telephone)
{
  for (size_t i = 0; i < _data->TelefoneTam; i++)
  {
    if (_data->telefones[i].id == _telephone->id)
    {
      if (strlen(_telephone->Telefone) > 0)
      {
        strcpy(_data->telefones[i].Telefone, _telephone->Telefone);
      }

      if (_telephone->Idhumano > 0 && personExists(_data, _telephone->Idhumano))
      {
        _data->telefones[i].Idhumano = _telephone->Idhumano;
      }

      return;
    }
  }

  printf("Não há telefone nesse id\n");
}

void ModEmail(CadastroPessoa *_data, Email *_email)
{
  for (size_t i = 0; i < _data->EmailTam; i++)
  {
    if (_data->emails[i].Id == _email->Id)
    {
      if (strlen(_email->email) > 0)
      {
        strcpy(_data->emails[i].email, _email->email);
      }

      if (_email->Idhumano > 0 && personExists(_data, _email->Idhumano))
      {
        _data->emails[i].Idhumano = _email->Idhumano;
      }

      return;
    }
  }

  printf("Não há email nesse id!\n");
}

void ExcluirPessoa(CadastroPessoa *_data, int _id)
{
  for (size_t i = 0; i < _data->PessoaTam; i++)
  {
    if (_data->Humano[i].id == _id)
    {
      for (size_t j = i + 1; j < _data->PessoaTam; j++)
        _data->Humano[j - 1] = _data->Humano[j];

      _data->PessoaTam--;
      _data->Humano = realloc(_data->Humano, sizeof(CadPessoa) * _data->PessoaTam);

      for (size_t j = 0; j < _data->TelefoneTam; j++)
      {
        if (_data->telefones[j].Idhumano == _id)
        {
          for (size_t k = j + 1; k < _data->TelefoneTam; k++)
          {
            _data->telefones[k - 1] = _data->telefones[k];
          }

          _data->TelefoneTam--;
          _data->telefones = realloc(_data->telefones, sizeof(Telefone) * _data->TelefoneTam);
        }
      }
      for (size_t j = 0; j < _data->EmailTam; j++)
      {
        if (_data->emails[j].Idhumano == _id)
        {
          for (size_t k = j + 1; k < _data->EmailTam; k++)
          {
            _data->emails[k - 1] = _data->emails[k];
          }

          _data->EmailTam--;
          _data->emails = realloc(_data->emails, sizeof(Email) * _data->EmailTam);
        }
      }

      return;
    }
  }

  printf("Id não encontrado!\n");
}

void ExcluirTelefone(CadastroPessoa *_data, int _id)
{
  for (size_t i = 0; i < _data->TelefoneTam; i++)
  {
    if (_data->telefones[i].id == _id)
    {
      for (size_t j = i + 1; j < _data->TelefoneTam; j++)
        _data->telefones[j - 1] = _data->telefones[j];

      _data->TelefoneTam--;
      _data->telefones = realloc(_data->telefones, sizeof(Telefone) * _data->TelefoneTam);

      return;
    }
  }

  printf("Não há telefone nesse id\n");
}

void ExcluirEmail(CadastroPessoa *_data, int _id)
{
  for (size_t i = 0; i < _data->EmailTam; i++)
  {
    if (_data->emails[i].Id == _id)
    {
      for (size_t j = i + 1; j < _data->EmailTam; j++)
        _data->emails[j - 1] = _data->emails[j];

      _data->EmailTam--;
      _data->emails = realloc(_data->emails, sizeof(Email) * _data->EmailTam);

      return;
    }
  }

  printf("Não há telefone nesse id\n");
}