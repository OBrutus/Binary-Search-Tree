#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define LEFT 1
#define RIGHT 0

typedef struct Node{
	int data;
	struct Node *left,*right;
	int level;
}Node;

typedef struct BST{
	Node* root;
	int cnt;
	int height;
	int numberOfLeafNodes;
	int balanceFactor;
}BST;

//int refreshTree(BST*);

Node* createNode(int data,int level){
	Node* a=(Node*)malloc(sizeof(Node));
	a->data=data;
	a->left=a->right=NULL;
	a->level=level;
	return a;
}

BST* createBST(int data){
	BST* tree=(BST*)malloc(sizeof(BST));
	tree->root=createNode(data,0);
	tree->cnt=1;
	tree->height=1;
	tree->numberOfLeafNodes=tree->balanceFactor=0;
	return tree;
}

Node* getMaxNode(Node* root){
	Node* a=root->right;
	while(a->right!=NULL)
		a=a->right;
	return a;
}

Node* getMinNode(Node* root){
	Node* a=root->left;
	while(a->left!=NULL)
		a=a->left;
	return a;
}

Node* getNode(Node* root,int data){
	while(root!=NULL && root->data!=data){
		if(root->data > data)
			root=root->right;
		else
			root=root->left;
	}
	return root;
}

Node* getParentNode(Node* root,int data){
	Node* temp;
	if(data==root->data)
		return NULL;
	while(data!=root->data){
		temp=root;
		if(data > root->data)
			root=root->right;
		else if(data < root->data)
			root=root->left;
	}
	return temp;
}

int nodeCpy(Node* dest,Node* src){
	dest->data=src->data;
	dest->level=src->level;
	return 0;
}

int printBFS(BST* tree,Node* rott){
	printf("BFS Complete it!\n");
	return 0;
}
int printPreorder(BST* tree,Node* root){
	if(root==NULL)
		return 0;
	printf("%4d \t%d\n",root->data,root->level);
	printPreorder(tree,root->left);
	printPreorder(tree,root->right);
	return 0;
}
int printInorder(BST* tree,Node* root){
	if(root==NULL)
		return 0;
	printInorder(tree,root->left);
	printf("%4d \t%d\n",root->data,root->level);
	printInorder(tree,root->right);
	return 0;
}
int printPostorder(BST* tree,Node* root){
	if(root==NULL)
		return 0;
	printPostorder(tree,root->left);
	printPostorder(tree,root->right);
	printf("%4d \t%d\n",root->data,root->level);
	return 0;
}

int printTree(BST* tree,Node* root){
	int ch=1;
	int isAdv=0;
	Node* temp=root;
	do{
		printf("  1:Preorder\n  2:Inorder\n");
		printf("  3:Postorder\n  4:BFS, Level by level\n");
		printf("  0:Exit\n    __opt__:");
		scanf("%d",&ch);
		if(!ch)
			return 0;
	}while(ch<1 && ch>4);
	printf(" Do you want advanced option for printing ? [0:NO , otherwise yes] -> ");
	scanf("%d",&isAdv);
	if(isAdv){
		printf("Adv. option provides :\n");
		printf("  1:Printing the subtree\n");
		printf("  2:Normal printing\n");
		scanf("%d",&isAdv);
		switch(isAdv){
			case 1:
				printf("Enter root of subtree");
				scanf("%d",&isAdv);//just reused variable isAdv
				temp=getNode(root,isAdv);
				if(temp==NULL){
					printf("Node not present or may be root!");
					printf("Printing normal Mode.");
					temp=root;
				}
				break;
			default :
				printf("Wrong input!\nPrinting Normally.\n");
				temp=root;
		}
	}
	switch(ch){
		case 1:
			printf("Preorder traversal is :\n");
			printPreorder(tree,temp);
			break;
		case 2:
			printf("Inorder traversal is :\n");
			printInorder(tree,temp);
			break;
		case 3:
			printf("Postorder traversal is:\n");
			printPostorder(tree,temp);
		case 4:
			printf("BFS :\n");
			printBFS(tree,temp);
	}
	return 0;
}

Node* ins(BST* tree,Node* root,Node* newNode,int* flg){
	int data=newNode->data;
	if(root==NULL){
		return newNode;
	}
	if(data > root->data){
		root->right=ins(tree,root->right,newNode,flg);
	} else if(data < root->data){
		root->left=ins(tree,root->left,newNode,flg);
	} else {
		printf("Data Exists\n");
		*flg=-1;
		return newNode;
	}
	newNode->level++;
	if(newNode->level+1 > tree->height)
		tree->height=newNode->level+1;
	return root;
}

int insertNode(BST* tree,int data){
	int flg=0;
	ins(tree,tree->root,createNode(data,0),&flg);
	if(flg!=-1) //ie, node inserted
		tree->cnt++;
	return 0;
}

Node* deleteNode(BST* tree,Node* root,int data){
	Node* temp=NULL;
	if(root->data==data){
		if(root->left==root->right){
			//it is child node
			root->data=-99;
			free(root);
			return NULL;
		} else if(root->right!= NULL && root->left==NULL){
			//has only right subtree
			temp=root->right;;
			printf("Deleted %d\n",root->data);
			free(root);
			return temp;
		} else if(root->left!=NULL && root->right==NULL){
			//has only left subtree
			temp=root->left;
			printf("Deleted %d\n",root->data);
			free(root);
			root=temp;
			return temp;
		} else {
			//has both subtree
			//take left pick max
			temp=getMaxNode(root->left);
			root->data=temp->data;
			//printf("Making %d's right as NULL",getParentNode(root->left,temp->data)->data);
			getParentNode(root->left,temp->data)->right=NULL;
			free(temp);
			return root;
		}
	} else if(data > root->data)
		root->right=deleteNode(tree,root->right,data);
	else
		root->left=deleteNode(tree,root->left,data);
	return NULL;
}

int main(){
	BST* tree;
	Node* temp; //used in 6
	int ch=1,var;
	while(ch){
		printf("1:Create Tree\n2:Insert\n3:Print\n4:Refresh and Tree Stat.\n");
		printf("5:Delete Node\n6:Know node info.\n");
		printf("7:Misc.\n8:Continious Insert\n");
		scanf("%d",&ch);
		switch(ch){
			case 0:
				printf("Exit!\n");
				exit(0);
			case 1:
				printf("root:");
				scanf("%d",&ch);
				tree=createBST(ch);
			break;
			case 2:
				printf("data:");
				scanf("%d",&ch);
				insertNode(tree,ch);
				break;
			case 3:
				printTree(tree,tree->root);
				break;
			case 4:
				//refreshTree(tree);
				printf("cnt.:\t%d\nht.:\t%d\n",tree->cnt,tree->height);
				break;
			case 5:
				printf("data:");
				scanf("%d",&ch);
				if(getNode(tree->root,ch)!=NULL)
					deleteNode(tree,tree->root,ch);
				else
					printf("404: data not found\n");
				break;
			case 6:
				printf("data:");
				scanf("%d",&ch);
				temp=getParentNode(tree->root, ch);
				if(temp==NULL){
					if(tree->root == temp){
						printf("I AM ROOT\n");
					} else
						printf("do not exist\n");
					break;
				}
				printf("****\n");
				printf("Parent data:%d\n",temp->data);
				var=temp->data;
				//now temp stores current node
				if(temp->data>ch)
					temp=temp->left;
				else
					temp=temp->right;
				printf("Current node info.:\n");
				printf("  data\t:%d\n  level=%d",temp->data,temp->level);
//				printf("  loc. adress\t:%u\n",temp);
				if(temp->left!=NULL)
					printf("left data:%d\n",temp->left->data);
				if(temp->right!=NULL)
					printf("right data:%d\n",temp->right->data);
				printf("*****\n");
				if(var > ch){
					printf("    %d\n",var);
					printf("  /\n");
				} else {
					printf("%d\n",var);
					printf("  \\\n");
				}
				printf("  %d\n",ch);
				printf(" /   \\\n");
				if(temp->left!=NULL)
					printf("%d   ",temp->left->data);
				else
					printf("<>   ");
				if(temp->right!=NULL)
					printf("%d\n",temp->right->data);
				else
					printf("<>\n");
					break;

			case 7:
				printf("Upcoming feature in new update...\nThis includes\n");
				printf("Clearing Console\nSaving tree to file\n");
				printf("and lot more ...!\nStay Tuned.\n");
			default:
				fflush(stdin);
				printf("Wrong input !!\nEnter valid input!!");
				fflush(stdin);
		}
		ch=1;
	}//end while
	/*
	*
	*
	*
	*
	*
	scanf("%d",&ch);
	tree=createBST(ch);
	scanf("%d%d",&ch,&var);
	insertNode(tree,ch);
	insertNode(tree,var);
	printTree(tree,tree->root);
	*/
	printf("\n");
	return 0;
}

/*int refreshTree(BST* tree){
	int minHeight=log(tree->cnt)/log(2);
	printf("in refresh min height:%d\n",minHeight);
	return 0;
}*/
