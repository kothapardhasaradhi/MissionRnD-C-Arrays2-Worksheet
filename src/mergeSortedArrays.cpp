/*
OVERVIEW: You are given 2 bank statements that are ordered by date - 
Write a function that produces a single merged statement ordered by dates.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[2] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" } };
Output: { { 10, "09-10-2003", "First" }, { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" },  30, "03-03-2005", "Third" }, { 220, "18-01-2010", "Sixth" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Combined statement ordered by transaction date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>

struct transaction {
	int amount;
	char date[11];
	char description[20];
};
int check(char *p, int *d, int *m, int *y)
{
	int  i, j, k, c = 0, t;
	*d = 0; *m = 0; *y = 0;
	for (i = 0; *(p + i) != '-'; i++)//converting date from char to int
	{
		if (*d>-1 && *d<32)
			*d = (*d * 10) + (*(p + i) - '0');
		else
			return 0;

	}
	for (k = i + 1; *(p + k) != '-'; k++)
	{
		if (*m>-1 && *m<13)
			*m = (*m * 10) + (*(p + k) - '0');//converting month from char to int
		else
			return 0;
	}
	for (j = k + 1; *(p + j) != '\0'; j++)
	{
		t = *(p + j) - '0';
		//	printf("%d\n", t);
		if (t<10 && t>-1)
		{
			*y = (*y * 10) + (*(p + j) - '0');	//converting year from char to int
			//     `       printf("%d\n",t);
		}
		else
			return 0;
	}
	if (*d < 1 || *m < 1 || *y<1)
		return 0;//date is wrong
	else
	{
		if (*m == 2)
		{
			if ((*d < 30) && (*y % 4 == 0))
				return 1;//date is correct
			else
			{
				if ((*d>0) && (*d < 29))
					return 1;//date is correct
				else
					return 0;//date is wrong
			}
		}
		else
		{
			if (((*m == 4) || (*m == 6) || (*m == 9) || (*m == 11)) && (*d < 31))
				return 1;

			else
			{
				if (((*m == 1) || (*m == 3) || (*m == 5) || (*m == 7) || (*m == 8) || (*m == 10) || (*m == 12)) && (*d < 32))
					return 1;
				else
					return 0;
			}
		}
	}


}



int isOlder(char *dob1, char *dob2)
{
	int d1, m1, y1, d2, m2, y2;
	int c1 = check(dob1, &d1, &m1, &y1);
	int c2 = check(dob2, &d2, &m2, &y2);
	if (c1 != 0 && c2 != 0)
	{
		if (y1 < y2)
			return 1;
		if (y2 < y1)
			return 2;
		if (y2 == y1)
		{
			if (m1 < m2)
				return  1;
			if (m2 < m1)
				return 2;
			if (m1 == m2)
			{
				if (d1 < d2)
					return 1;
				if (d1 > d2)
					return 2;
				if (d1 == d2)
					return 0;
			}
		}

	}
	else
		return -1;
}
struct transaction * mergeSortedArrays(struct transaction *A, int ALen, struct transaction *B, int BLen) 
{
	if (A != NULL&&B != NULL)
	{
		int i, j, k, flag;
		struct transaction *c;
		c = (struct transaction*)malloc((ALen + BLen)*sizeof(struct transaction));
		for (i = 0, j = 0, k = 0; k < ALen + BLen; k++)
		{
			if (i < ALen&&j < BLen)
			{
				flag = isOlder(A[i].date, B[j].date);
				if (flag == 1)
				{
					c[k] = A[i];
					i++;
				}
				if (flag == 2)
				{
					c[k] = B[j];
					j++;
				}
				if (flag == 0)
				{
					c[k] = A[i];
					i++;
					k++;
					c[k] = B[j];
					j++;
				}
			}
			else
			{
				if (i < ALen)
				{
					c[k] = A[i];
					i++;
				}
				if (j < BLen)
				{
					c[k] = B[j];
					j++;
				}
			}
		}
		return c;
	}
	else
		return NULL;
	/*{
		if (A == NULL)
		{
			return B;
		}
		if (B == NULL)
		{
			return A;
		}
	}*/
	
}