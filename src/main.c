#include "main.h"

#include <_xlocale.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <xlocale.h>

void AddNode(Head** head, long data) {
  Node* node = malloc(sizeof(Node));

  if (node == NULL) {
    return;
  }

  node->data = data;
  node->next_node = NULL;

  if ((*head) == NULL) {
    (*head) = malloc(sizeof(Head));

    if ((*head) == NULL) {
      free(node);

      return;
    }

    (*head)->first_node = node;

    return;
  }

  Node* current_node = (*head)->first_node;

  while (current_node->next_node != NULL) {
    current_node = current_node->next_node;
  }

  current_node->next_node = node;
}

bool RemoveNode(Head** head, long data) {
  if ((*head) == NULL) {
    printf("Operation failed. List is empty.\n");

    return false;
  }

  Node* current_node = (*head)->first_node;
  Node* previous_node = current_node;

  while (current_node->next_node != NULL) {
    if (current_node->data != data) {
      previous_node = current_node;
      current_node = current_node->next_node;

      continue;
    }

    break;
  }

  if (current_node->data != data) {
    printf("The entered number could not be found in the list.\n");

    return false;
  }

  if (current_node == previous_node && current_node->next_node == NULL) {
    free(current_node);
    free((*head));
    (*head) = NULL;

    return true;
  }

  if ((*head)->first_node == current_node) {
    (*head)->first_node = current_node->next_node;

    free(current_node);

    return true;
  }

  previous_node->next_node = current_node->next_node;

  free(current_node);

  return true;
}

bool InsertNode(Head** head, NodeOptions node_options) {
  if ((*head) == NULL) {
    printf("Could not insert node into the list. List is empty.\n");

    return false;
  }

  Node* current_node = (*head)->first_node;
  Node* previous_node = current_node;

  for (int i = 0; i < node_options.index; i++) {
    previous_node = current_node;
    current_node = current_node->next_node;

    if (current_node == NULL) {
      printf(
          "Requested index is higher than the number of nodes in the list.\n");

      return false;
    }
  }

  Node* node = malloc(sizeof(Node));

  if (node == NULL) {
    return false;
  }

  node->data = node_options.data;
  node->next_node = current_node;
  previous_node->next_node = node;

  return true;
}

void PrintList(Head** head) {
  if ((*head) == NULL) {
    printf("List is empty.\n");

    return;
  }

  Node* current_node = (*head)->first_node;

  wprintf(L"%lc HEAD %lc %p %lc %lc ", kVerticalLine, kVerticalLineDashed,
          (*head)->first_node, kVerticalLine, kArrow);

  while (current_node != NULL) {
    if (current_node->next_node == NULL) {
      wprintf(L"%lc %d %lc %p %lc %lc NULL", kVerticalLine, current_node->data,
              kVerticalLineDashed, current_node->next_node, kVerticalLine,
              kArrow);
    } else {
      wprintf(L"%lc %d %lc %p %lc %lc ", kVerticalLine, current_node->data,
              kVerticalLineDashed, current_node->next_node, kVerticalLine,
              kArrow);
    }

    current_node = current_node->next_node;
  }

  printf("\n");
}

void PrintMenu() {
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

bool IsScanfInputValid(int input) {
  if (input == EOF || input != 1) {
    printf("Invalid input. Try again.\n");

    while (fgetc(stdin) != '\n') {
      ;
    }

    return false;
  }

  return true;
}

void PrintOperationFailedMessage() { printf("Operation failed.\n"); }

int main() {
  locale_t locale = newlocale(LC_CTYPE, "en_US", NULL);
  uselocale(locale);

  Head* head = NULL;
  char* option_id_input = malloc(sizeof(char));
  long option_id = -1;
  char* input_one_string = malloc(sizeof(char));
  char* input_two_string = malloc(sizeof(char));

  PrintMenu();

  while (option_id != kQuit) {
    int number_of_assigned_input_items = 0;
    char* end = NULL;
    long input_one_long = 0;
    long input_two_long = 0;
    bool success = false;

    printf("Select an option: ");
    // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
    number_of_assigned_input_items = scanf("%s", option_id_input);
    option_id = strtol(option_id_input, &end, kBase);

    if (!IsScanfInputValid(number_of_assigned_input_items)) {
      continue;
    }

    switch (option_id) {
      // Add
      case kAdd:
        printf("Enter the number you want to save in the node: ");
        // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
        number_of_assigned_input_items = scanf("%s", input_one_string);
        input_one_long = strtol(input_one_string, &end, kBase);

        if (!IsScanfInputValid(number_of_assigned_input_items)) {
          break;
        }

        AddNode(&head, input_one_long);

        break;

        // Remove
      case kRemove:
        printf("Enter the number you want to remove from the list: ");
        // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
        number_of_assigned_input_items = scanf("%s", input_one_string);
        input_one_long = strtol(input_one_string, &end, kBase);

        if (!IsScanfInputValid(number_of_assigned_input_items)) {
          continue;
        }

        success = RemoveNode(&head, input_one_long);

        if (!success) {
          PrintOperationFailedMessage();
        }

        break;

        // Insert
      case kInsert:
        printf("Enter the number you want to save in the node: ");
        // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
        number_of_assigned_input_items = scanf("%s", input_one_string);
        input_one_long = strtol(input_one_string, &end, kBase);

        if (!IsScanfInputValid(number_of_assigned_input_items)) {
          continue;
        }

        printf("Enter the index at which you want to add the node: ");
        // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
        number_of_assigned_input_items = scanf("%s", input_two_string);
        input_two_long = strtol(input_one_string, &end, kBase);

        if (!IsScanfInputValid(number_of_assigned_input_items)) {
          continue;
        }

        success = InsertNode(
            &head, (struct NodeOptions){input_one_long, input_two_long});

        if (!success) {
          PrintOperationFailedMessage();
        }

        break;

        // Print
      case kPrint:
        PrintList(&head);
        break;

        // Quit
      case kQuit:
        break;

        // Invalid
      default:
        printf("Invalid option selected. Try again.\n");
        break;
    }
  }

  free(head);
  free(option_id_input);
  free(input_one_string);
  free(input_two_string);
  freelocale(locale);

  return 0;
}
