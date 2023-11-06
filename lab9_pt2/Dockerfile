#Set the base image to use
FROM gcc:latest
# Copy the C program into the container
COPY nflscore.c .
# Compile the C program
RUN gcc -o nflscore nflscore.c
# Set the command to run when the container starts
CMD ["./nflscore"]