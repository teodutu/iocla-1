unsigned int num_items = 10;

extern void (*operator)(void);

int main(void)
{
	num_items = 5;
	operator();

	return 0;
}
