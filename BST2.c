//Binary search tree

#include<stdio.h>
#include<stdlib.h>
#define null 0 
#define and &&
#define or ||


typedef struct tree_node{
	int data;
	struct tree_node* lc;
	struct tree_node* rc;
}*node;

node root = null , temp2 , neww , temp , temp1; 
node stack[10];
int top = -1;
node pop(){
	return stack[top--];
}
void push(node temp){
	stack[++top] = temp;
}

int n;
/*		function declarations	*/

node find_max(node temp);
node find_min(node temp);
node search(int x, node temp);
void insert(int x, node temp,node neww);
node delete(int x , node temp);
void inorder_traversal(node temp);
void postorder_traversal(node temp);
void peorder_traversal(node temp);
void make_empty(node temp);

/*		function definations	*/

node find_max(node temp){
	if(temp){
	if(temp->rc){
		return find_max(temp->rc);
	}
	else{
		return temp;
	}
	}
	else{
	printf("\nTree is empty\n");
	return null;
	}
}

node find_min(node temp){
	if(temp){
	if(temp->lc){
		return find_min(temp->lc);
	}
	else{
		return temp;
	}
	}
	else{
	printf("\nTree is empty\n");
	return null;
	}
}

node search(int x, node temp){
	if(!temp){
		return null;
	}
	else if(temp->data>x){
		return search(x,temp->lc);
	}
	else if(temp->data<x){
		return search(x,temp->rc);
	}
	else{
		return temp;
	}
}

void insert(int x,node temp,node neww){
	if(!temp ){
		root = neww;	
	}
	else{
	if(x > temp->data){
		if(temp->rc)
			insert(x,temp->rc,neww);
		else
			temp->rc = neww;
	}
	else if(x < temp->data){
		if(temp->lc)
			insert(x,temp->lc,neww);
		else
			temp->lc = neww;
	}
	else{
		printf("\nValue already exists\n");
		return ;
	}
	}
}

node delete( int x , node temp){
	if(x<temp->data){
		temp->lc = delete(x,temp->lc);
	}
	else if(x>temp->data){
		temp->rc = delete(x,temp->rc);
	}
	else if(temp->lc and temp->rc){					//node with 2 children
		temp1 = find_min(temp->rc);
		temp->data = temp1->data;
		temp->rc = delete(temp->data , temp->rc);
	}
	else{											//node with 1 or 0 children
		temp1 = temp;
		if(temp->lc)
			{
				temp = temp->lc;
				free(temp1);
			}
		else if(temp->rc)
			{
				temp= temp->rc;
				free(temp1);
			}
		else{
			free(temp1);
			temp = null;
		}
	}
	return temp;
}

		void inorder_traversal(node temp){
			while(1){
				while(temp){
					push(temp);
					temp = temp->lc;
				}
				if(top == -1)
				break;
				temp = pop();
				printf("%d, ",temp->data);
				temp = temp->rc;
			}	
		}
		
		void postorder_traversal(node temp){
			do{
				while(temp){
					if(temp->rc)
						push(temp->rc);
					push(temp);
					temp = temp->lc;
				}
				temp = pop();
				if(temp->rc && stack[top] == temp->rc){
					pop();
					push(temp);
					temp = temp->rc;
				}
				else{
					printf("%d, ",temp->data);
					temp = null;
				}
			}while(top!=-1);
			
		}

void preorder_traversal(node temp){

while(1){
	while(temp){
		printf("%d, ",temp->data);
		push(temp);
		temp = temp->lc;
	}
	if(top == -1)
	break;
	temp = pop();
	temp = temp->rc;
	
}

}

void make_empty(node temp){
	
	if(!temp){
		return ;
	}
	else{
		make_empty(temp->lc);
		make_empty(temp->rc);
		free(temp);
	}
}


int main(){
	
	int x,ch;
	while(1){
	printf("\n1.insert\n2.delete\n3.search an element\n4.find minimum\n5.find maximum\n6.make empty\n7.inorder traversal\n8.postorder traversal\n9.preorder traversal\n10.terminate\n\n");
	scanf("%d",&ch);
	switch(ch){
		case 1:
			printf("\nEnter an element:\t");
			scanf("%d",&x);
			neww = (node)calloc(sizeof(node),1);
			neww->data = x;
			insert(x,root,neww);
			break;
		case 2:
			printf("\nEnter an element:\t");
			scanf("%d",&x);
			if(search(x,root)){
			if(delete(x,root))
				printf("\n%d deleted from the tree\n",x);
			}
			else
			printf("\n%d is not present in the tree\n",x);
			break;
		case 3:
			printf("\nEnter an element:\t");
			scanf("%d",&x);
			temp1 = search(x,root);
			if(temp1)
				printf("\n%d found at location %d\n",temp1->data,temp1);
			else
				printf("\n%d not found\n",x);
			break;
		case 4:
			temp1 = find_min(root);
			if(temp1)
			printf("\n%d is the minimum element in the tree at the location %d\n",temp1->data,temp1);
			break;
		case 5:
			temp1 = find_max(root);
			if(temp1)
			printf("\n%d is the maximum element in the tree at the location %d\n",temp1->data,temp1);
			break;
		case 6:
			make_empty(root);
			printf("\nThe tree is cleared\n");
			break;
		case 7:
			printf("\nInorder traversal:\t");
			inorder_traversal(root);
			break;
		case 8:
			printf("\nPostorder traversal:\t");
			postorder_traversal(root);
			break;
		case 9:
			printf("\nPreorder traversal:\t");
			preorder_traversal(root);
			break;
		case 10:
			goto A;
			break;
		default:printf("\nInvalid choice\n");
	}
}
	A:return 0;
}
