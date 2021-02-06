- init:
    run: rm -f q2.o q2
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror  q2.c -o q2  # timeout: 2
    blocker: true

- case0:
    run: ./q2
    points:
    script:
        - expect: 'Welcome to the movie database\.\r\nEnter your request \(1 for getting the purchases of a movie, 2 for updating the rating of a movie, 3 for exit\):'      # timeout: 2
        - send: "1"
        - expect: "Enter the movie title:"      # timeout: 2
        - send: "Ben Hur"
        - expect: 'The movie Ben Hur has been purchased 5 times\.\r\nEnter your request \(1 for getting the purchases of a movie, 2 for updating the rating of a movie, 3 for exit\):'      # timeout: 2
        - send: "3"
    return: 0

- case1:
    run: ./q2
    points:
    script:
        - expect: 'Welcome to the movie database\.\r\nEnter your request \(1 for getting the purchases of a movie, 2 for updating the rating of a movie, 3 for exit\):'      # timeout: 2
        - send: "2"
        - expect: "Enter the movie title:"      # timeout: 2
        - send: "Spartacus"
        - expect: 'Enter the movie rating \(out of 5\):'     # timeout: 2
        - send: "5"
        - expect: 'The movie Spartacus is updated\. The number of purchases is 10\. The rating is updated to 4\.10\.\r\nEnter your request \(1 for getting the purchases of a movie, 2 for updating the rating of a movie, 3 for exit\):'      # timeout: 2
        - send: "3"
    return: 0

- case2:
    run: ./q2
    points:
    script:
        - expect: 'Welcome to the movie database\.\r\nEnter your request \(1 for getting the purchases of a movie, 2 for updating the rating of a movie, 3 for exit\):'      # timeout: 2
        - send: "2"
        - expect: "Enter the movie title:"      # timeout: 2
        - send: "Harry Potter"
        - expect: 'Enter the movie rating \(out of 5\):'     # timeout: 2
        - send: "1"
        - expect: 'The movie Harry Potter could not be found in the database\. Would you like to add this movie \(Y/N\):'      # timeout: 2
        - send: "Y"
        - expect: 'The movie Harry Potter is added to the database with a rating of 1\.\r\nEnter your request \(1 for getting the purchases of a movie, 2 for updating the rating of a movie, 3 for exit\):'      # timeout: 2
        - send: "1"
        - expect: "Enter the movie title:"      # timeout: 2
        - send: "Harry Potter"
        - expect: 'The movie Harry Potter has been purchased 1 times\.\r\nEnter your request \(1 for getting the purchases of a movie, 2 for updating the rating of a movie, 3 for exit\):'      # timeout: 2
        - send: "2"
        - expect: "Enter the movie title:"      # timeout: 2
        - send: "Harry Potter"
        - expect: 'Enter the movie rating \(out of 5\):'      # timeout: 2
        - send: "5"
        - expect: 'The movie Harry Potter is updated\. The number of purchases is 2\. The rating is updated to 3\.00\.\r\nEnter your request \(1 for getting the purchases of a movie, 2 for updating the rating of a movie, 3 for exit\):'      # timeout: 2
        - send: "1"
        - expect: "Enter the movie title:"      # timeout: 2
        - send: "Harry Potter"
        - expect: 'The movie Harry Potter has been purchased 2 times\.\r\nEnter your request \(1 for getting the purchases of a movie, 2 for updating the rating of a movie, 3 for exit\):'      # timeout: 2
        - send: "3"
    return: 0

- case3:
    run: ./q2
    points:
    script:
        - expect: 'Welcome to the movie database\.\r\nEnter your request \(1 for getting the purchases of a movie, 2 for updating the rating of a movie, 3 for exit\):'      # timeout: 2
        - send: "1"
        - expect: "Enter the movie title:"      # timeout: 2
        - send: "Harry Potter"
        - expect: 'The movie Harry Potter could not be found in the database\.\r\nEnter your request \(1 for getting the purchases of a movie, 2 for updating the rating of a movie, 3 for exit\):'      # timeout: 2
        - send: "2"
        - expect: "Enter the movie title:"      # timeout: 2
        - send: "A Beautiful Mind"
        - expect: 'Enter the movie rating \(out of 5\):'     # timeout: 2
        - send: "6"
        - expect: 'Enter the movie rating \(out of 5\):'     # timeout: 2
        - send: "5"
        - expect: 'The movie A Beautiful Mind could not be found in the database\. Would you like to add this movie \(Y/N\):'
        - send: "y"
        - expect: 'Please enter a valid input \(Y/N\):'
        - send: "Y"
        - expect: 'The movie A Beautiful Mind is added to the database with a rating of 5\.\r\nEnter your request \(1 for getting the purchases of a movie, 2 for updating the rating of a movie, 3 for exit\):' # timeout: 2
        - send: "2"
        - expect: "Enter the movie title:"      # timeout: 2
        - send: "A Beautiful Mind"
        - expect: 'Enter the movie rating \(out of 5\):'     # timeout: 2
        - send: "4"
        - expect: 'The movie A Beautiful Mind is updated\. The number of purchases is 2\. The rating is updated to 4\.50\.\r\nEnter your request \(1 for getting the purchases of a movie, 2 for updating the rating of a movie, 3 for exit\):'      # timeout: 2
        - send: "1"
        - expect: "Enter the movie title:"      # timeout: 2
        - send: "A Beautiful Mind"
        - expect: 'The movie A Beautiful Mind has been purchased 2 times\.\r\nEnter your request \(1 for getting the purchases of a movie, 2 for updating the rating of a movie, 3 for exit\):'
        - send: "3"
    return: 0



