#include "../../inc/minishell.h"

void	*ft_recalloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (old_size == new_size)
		return (ptr);
	if (ptr == NULL)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memcpy(new_ptr, ptr, old_size);
	// free(&ptr);
	return (new_ptr);
}
