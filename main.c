#include "main.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

void addNode(Head **ppHead, long data) {
  Node *pNode = malloc(sizeof(Node));

  if (pNode == NULL) {
    return;
  }

  pNode->data = data;
  pNode->pNextNode = NULL;

  if ((*ppHead) == NULL) {
    (*ppHead) = malloc(sizeof(Head));

    if ((*ppHead) == NULL) {
      free(pNode);

      return;
    }

    (*ppHead)->pFirstNode = pNode;

    return;
  }

  Node *pCurrentNode = (*ppHead)->pFirstNode;

  while (pCurrentNode->pNextNode != NULL) {
    pCurrentNode = pCurrentNode->pNextNode;
  }

  pCurrentNode->pNextNode = pNode;
}

bool removeNode(Head **ppHead, long data) {
  if ((*ppHead) == NULL) {
    printf("Operation failed. List is empty.\n");

    return false;
  }

  Node *pCurrentNode = (*ppHead)->pFirstNode;
  Node *pPreviousNode = pCurrentNode;

  while (pCurrentNode->pNextNode != NULL) {
    if (pCurrentNode->data != data) {
      pPreviousNode = pCurrentNode;
      pCurrentNode = pCurrentNode->pNextNode;

      continue;
    }

    break;
  }

  if (pCurrentNode->data != data) {
    printf("The entered number could not be found in the list.\n");

    return false;
  }

  if (pCurrentNode == pPreviousNode && pCurrentNode->pNextNode == NULL) {
    free(pCurrentNode);
    free((*ppHead));
    (*ppHead) = NULL;

    return true;
  }

  if ((*ppHead)->pFirstNode == pCurrentNode) {
    (*ppHead)->pFirstNode = pCurrentNode->pNextNode;

    free(pCurrentNode);

    return true;
  }

  pPreviousNode->pNextNode = pCurrentNode->pNextNode;

  free(pCurrentNode);

  return true;
}

bool insertNode(Head **ppHead, long data, long index) {
  if ((*ppHead) == NULL) {
    printf("Could not insert node into the list. List is empty.\n");

    return false;
  }

  Node *pCurrentNode = (*ppHead)->pFirstNode;
  Node *pPreviousNode = pCurrentNode;

  for (int i = 0; i < index; i++) {
    pPreviousNode = pCurrentNode;
    pCurrentNode = pCurrentNode->pNextNode;

    if (pCurrentNode == NULL) {
      printf(
          "Requested index is higher than the number of nodes in the list.\n");

      return false;
    }
  }

  Node *pNode = malloc(sizeof(Node));

  if (pNode == NULL) {
    return false;
  }

  pNode->data = data;
  pNode->pNextNode = pCurrentNode;
  pPreviousNode->pNextNode = pNode;

  return true;
}

void printList(Head **ppHead) {
  if ((*ppHead) == NULL) {
    printf("List is empty.\n");

    return;
  }

  Node *pCurrentNode = (*ppHead)->pFirstNode;

  wprintf(L"%lc HEAD %lc %p %lc %lc ", g_v_line, g_v_line_dashed,
          (*ppHead)->pFirstNode, g_v_line, g_arrow);

  while (pCurrentNode != NULL) {
    if (pCurrentNode->pNextNode == NULL) {
      wprintf(L"%lc %d %lc %p %lc %lc NULL", g_v_line, pCurrentNode->data,
              g_v_line_dashed, pCurrentNode->pNextNode, g_v_line, g_arrow);
    } else {
      wprintf(L"%lc %d %lc %p %lc %lc ", g_v_line, pCurrentNode->data,
              g_v_line_dashed, pCurrentNode->pNextNode, g_v_line, g_arrow);
    }

    pCurrentNode = pCurrentNode->pNextNode;
  }

  printf("\n");
}

void printMenu() {
  printf("Singly-linked list interactive CLI\n");
  printf("\n");

  printf("Press a number to select one of the following options:\n");
  printf("\t(1) Add\n");
  printf("\t(2) Remove\n");
  printf("\t(3) Insert\n");
  printf("\t(4) Print\n");
  printf("\t(5) Quit\n");
  printf("\n");
}

bool isScanfInputValid(int input) {
  if (input == EOF || input != 1) {
    printf("Invalid input. Try again.\n");

    while (fgetc(stdin) != '\n')
      ;

    return false;
  }

  return true;
}

void printOperationFailedMessage() { printf("Operation failed.\n"); }

int main() {
  setlocale(LC_CTYPE, "");
  Head *pHead = NULL;
  char *optionIdInput = malloc(sizeof(char));
  long optionId = -1;
  char *inputOneString = malloc(sizeof(int));
  char *inputTwoString = malloc(sizeof(int));

  printMenu();

  while (optionId != 5) {
    int numberOfAssignedInputItems;
    char *end;
    long inputOneLong;
    long inputTwoLong;
    bool success;

    printf("Select an option: ");
    numberOfAssignedInputItems = scanf("%s", optionIdInput);
    optionId = strtol(optionIdInput, &end, 10);

    if (!isScanfInputValid(numberOfAssignedInputItems)) {
      continue;
    }

    switch (optionId) {
      // Add
      case 1:
        printf("Enter the number you want to save in the node: ");
        numberOfAssignedInputItems = scanf("%s", inputOneString);
        inputOneLong = strtol(inputOneString, &end, 10);

        if (!isScanfInputValid(numberOfAssignedInputItems)) {
          break;
        }

        addNode(&pHead, inputOneLong);

        break;

        // Remove
      case 2:
        printf("Enter the number you want to remove from the list: ");
        numberOfAssignedInputItems = scanf("%s", inputOneString);
        inputOneLong = strtol(inputOneString, &end, 10);

        if (!isScanfInputValid(numberOfAssignedInputItems)) {
          continue;
        }

        success = removeNode(&pHead, inputOneLong);

        if (!success) {
          printOperationFailedMessage();
        }

        break;

        // Insert
      case 3:
        printf("Enter the number you want to save in the node: ");
        numberOfAssignedInputItems = scanf("%s", inputOneString);
        inputOneLong = strtol(inputOneString, &end, 10);

        if (!isScanfInputValid(numberOfAssignedInputItems)) {
          continue;
        }

        printf("Enter the index at which you want to add the node: ");
        numberOfAssignedInputItems = scanf("%s", inputTwoString);
        inputTwoLong = strtol(inputOneString, &end, 10);

        if (!isScanfInputValid(numberOfAssignedInputItems)) {
          continue;
        }

        success = insertNode(&pHead, inputOneLong, inputTwoLong);

        if (!success) {
          printOperationFailedMessage();
        }

        break;

        // Print
      case 4:
        printList(&pHead);
        break;

        // Quit
      case 5:
        break;

        // Invalid
      default:
        printf("Invalid option selected. Try again.\n");
        break;
    }
  }

  free(pHead);
  free(optionIdInput);
  free(inputOneString);
  free(inputTwoString);

  return 0;
}
