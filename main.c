#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	printf("%d", access("./hola.sh", X_OK));
}