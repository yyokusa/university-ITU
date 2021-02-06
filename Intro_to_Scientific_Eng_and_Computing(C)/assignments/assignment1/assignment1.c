#include <stdio.h>
#include <stdlib.h> // EXIT SUCCESS, EXIT_FAILURE

int main()
{
  int year;
  int initial_year;
  int month;
  int day;
  int end_year;
  int century_of_year; // zero - based century
  int two_digit_year;  // two digit year
  int day_of_the_week;
  int is_valid = 0;
  int check_day_of_the_week;

  printf("Enter date [year month day]: ");
  scanf("%d%d%d", &year, &month, &day);
  initial_year = year;

  // IS DATE VALID
  switch (month)
  {
  case 1:
    is_valid = ((day <= 31 && day >= 1) ? 1 : 0);
    break;
  case 2:
    is_valid = ((day <= 28 && day >= 1) ? 1 : 0);
    break;
  case 3:
    is_valid = ((day <= 31 && day >= 1) ? 1 : 0);
    break;
  case 4:
    is_valid = ((day <= 30 && day >= 1) ? 1 : 0);
    break;
  case 5:
    is_valid = ((day <= 31 && day >= 1) ? 1 : 0);
    break;
  case 6:
    is_valid = ((day <= 30 && day >= 1) ? 1 : 0);
    break;
  case 7:
    is_valid = ((day <= 31 && day >= 1) ? 1 : 0);
    break;
  case 8:
    is_valid = ((day <= 31 && day >= 1) ? 1 : 0);
    break;
  case 9:
    is_valid = ((day <= 30 && day >= 1) ? 1 : 0);
    break;
  case 10:
    is_valid = ((day <= 31 && day >= 1) ? 1 : 0);
    break;
  case 11:
    is_valid = ((day <= 30 && day >= 1) ? 1 : 0);
    break;
  case 12:
    is_valid = ((day <= 31 && day >= 1) ? 1 : 0);
    break;
  default:
    is_valid = 0;
    break;
  } // end switch

  // check if date is valid
  if (!is_valid)
  {
    printf("Invalid date.\n");
    return EXIT_FAILURE;
  }

  printf("Enter end year: ");
  scanf("%d", &end_year);

  if (month == 1 || month == 2)
  {
    month += 12;
    year -= 1;
    century_of_year = year / 100;
    two_digit_year = year % 100;
  }
  else
  {
    century_of_year = year / 100;
    two_digit_year = year % 100;
  }

  // zeller's congruence
  day_of_the_week = (day + (int)(13 * (month + 1) / 5.0) + two_digit_year +
                     (int)(two_digit_year / 4.0) +
                     (int)(century_of_year / 4.0) + 5 * century_of_year) %
                    7;

  switch (day_of_the_week)
  {
  case 0:
    printf("It's a Saturday.\n");
    break;
  case 1:
    printf("It's a Sunday.\n");
    break;
  case 2:
    printf("It's a Monday.\n");
    break;
  case 3:
    printf("It's a Tuesday.\n");
    break;
  case 4:
    printf("It's a Wednesday.\n");
    break;
  case 5:
    printf("It's a Thursday.\n");
    break;
  case 6:
    printf("It's a Friday.\n");
    break;
  default:
    printf("something went wrong line121");
    break;
  }

  check_day_of_the_week = day_of_the_week;
  int i;
  int res = 0;
  for (i = initial_year + 1; i <= end_year; i++)
  {
    int q = day;
    int m = month;
    int j;
    int k;
    if (m == 1 || m == 2)
    {
      m += 12;
      i -= 1;
      j = i / 100;
      k = i % 100;
      i += 1; //year is also loop variable
    }
    else
    {
      century_of_year = i / 100;
      two_digit_year = i % 100;
      j = century_of_year;
      k = two_digit_year;
    }
    // zeller's congruence
    day_of_the_week =
        (q + (13 * (m + 1) / 5) + k + (k / 4) + (j / 4) + 5 * j) % 7;
    // check if same weekday
    if (check_day_of_the_week == day_of_the_week)
    {
      ++res;
    }
  }
  printf("Same day-and-month on same weekday between %d and %d: %d\n",
         initial_year + 1, end_year, res);
  // end with success code
  return EXIT_SUCCESS;
}