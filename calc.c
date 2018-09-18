#include "calc.h"

int calc_input_check(const char *input, int size)
{
	static const char * const pre = "0123456789+-*/^() \t\r\n";
	stack tmp;
	stack_init(&tmp, size);

	for (; *input != '\0'; input++) {
		int i;
		for (i = 0; pre[i] != '\0' && pre[i] != *input; i++) ;
		if (pre[i] == '\0') {
			return 0;
		}
		if (*input == '(') {
			stack_push(&tmp, *input);
		} else if (*input == ')') {
			stack_pop(&tmp);
		}
	}

	int flag = stack_empty(&tmp);
	stack_free(&tmp);

	return flag;
}

stack_type calc_compute(const char *input, int size)
{
	stack operator, number, buffer, temp;
	stack_init(&operator, size);
	stack_init(&number, size);
	stack_init(&buffer, size);
	stack_init(&temp, size);
	stack_type resolt = 0;

    char ch;
    int end_flag;
	for (ch = 0, end_flag = 0; *input != '\0'; input++) {
        if ('0' <= *input && *input <= '9') {
            end_flag = 0;
        } else {
            end_flag = 1;
        }

        if (end_flag) {
            stack_push(&buffer, ']');
        }

        //优先级比较：
        //如果当前操作符比栈顶操作符优先级高，则直接压栈（这是个优先级栈，朝栈顶方向优先级越高），
        //否则先将栈顶操作数弹出，然后将当前操作数压栈。
		switch (*input) {
		case '+':
		case '-':
			if (!stack_empty(&operator) && (char)stack_peek(&operator) != '(') {
				stack_push(&buffer, stack_pop(&operator));
			}
			stack_push(&operator, *input);
			break;
		case '*':
		case '/':
			if (!stack_empty(&operator)) {
				ch = (char)stack_peek(&operator);
				if (ch == '*' || ch == '/' || ch == '^') {
					stack_push(&buffer, stack_pop(&operator));
				}
			}
			stack_push(&operator, *input);
			break;
		case '^':
			if (!stack_empty(&operator) && (char)stack_peek(&operator) == '^') {
				stack_push(&buffer, stack_pop(&operator));
			}
			stack_push(&operator, *input);
			break;
		case '(':
			stack_push(&operator, *input);
			break;
		case ')':
			while (!stack_empty(&operator) && (ch = (char)stack_pop(&operator)) != '(') {
				stack_push(&buffer, ch);
			}
			break;
		default:
            if ('0' <= *input && *input <= '9') {
                stack_push(&buffer, *input);
            }
			break;
		}
	}

    ch = (char)stack_peek(&buffer);
    if ('0' <= ch && ch <= '9') {
        stack_push(&buffer, ']');
    }

	while (!stack_empty(&operator)) {
		stack_push(&buffer, stack_pop(&operator));
	}

    int i;
	char * const str = stack_to_string(&buffer);
    stack_clear(&buffer);

	for (i = 0; str[i] != '\0'; i++) {
		if ('0' <= str[i] && str[i] <= '9') {
            stack_push(&buffer, str[i]);
		} else if (str[i] == ']') {
            stack_clear(&temp);
            while (!stack_empty(&buffer)) {
                ch = (char)stack_peek(&buffer);
                if ('0' <= ch && ch <= '9') {
                    stack_push(&temp, stack_pop(&buffer));
                } else {
                    break;
                }
            }
            if (!stack_empty(&temp)) {
                stack_type tmp_number = 0;
                while (!stack_empty(&temp)) {
                    tmp_number = tmp_number * 10 + (char)stack_pop(&temp) - '0';
                }
                stack_push(&number, tmp_number);
            }
        } else {
			stack_type number_right = stack_pop(&number);
			stack_type number_left = stack_pop(&number);
			switch (str[i]) {
			case '+':
				resolt = number_left + number_right;
				break;
			case '-':
				resolt = number_left - number_right;
				break;
			case '*':
				resolt = number_left * number_right;
				break;
			case '/':
                if (number_right == 0) {
                    resolt = 0;
                } else {
                    resolt = number_left * 1.0 / number_right;
                }
				break;
			case '^':
				resolt = 1;
				int i;
				for (i = 0; i < (int)number_right; i++) {
					resolt *= number_left;
				}
				break;
			default:
				break;
			}
			stack_push(&number, resolt);
		}
	}

	resolt = stack_pop(&number);

	stack_free(&operator);
	stack_free(&number);
	stack_free(&buffer);
	stack_free(&temp);
    free(str);

	return resolt;
}
