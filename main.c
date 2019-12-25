//
// Created by Евгений Ваганов on 25.12.2019.
//

#include "lem_in.h"


int line_analyzer(char *line)
{
	
	return (0);
}

int main()
{
	char *line;
	t_list	*farm;

	while (get_next_line(0, &line))
	{
		if (line_analyzer(line))
			farm_maker(line, &farm);
		else
			error_report
	}
}