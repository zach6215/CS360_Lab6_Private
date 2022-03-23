#ifndef repeat
#define repeat

#include "util.c"

/************* cd_ls_pwd.c file **************/
int cd()
{
  printf("cd: under construction READ textbook!!!!\n");

  int ino = getino(pathname);
  //ino doesn't exist
  if (ino == 0)
  {
    return -1;
  }
  MINODE *mip = iget(dev, ino);
  if (mip->INODE.i_mode == 16877)
  {
    iput(running->cwd);
    running->cwd = mip;
  }
  else
  {
    return -1;
  }
  // READ Chapter 11.7.3 HOW TO chdir
}

int ls_file(MINODE *mip, char *name)
{
  printf("ls_file: to be done: READ textbook!!!!\n");
  // READ Chapter 11.7.3 HOW TO ls
}

int ls_dir(MINODE *mip)
{
  printf("ls_dir: list CWD's file names; YOU FINISH IT as ls -l\n");

  INODE *ip;
  
  int ibuf[BLKSIZE/4];
  
  int dibuf[BLKSIZE/4];
  
  char buf[BLKSIZE], temp[256];
  DIR *dp;
  char *cp;

  printf("mip inode links count: %d", mip->INODE.i_links_count);
  printf("\n");

  mip->INODE;

   printf("================ Direct Blocks ===================\n");
   for (int i=0; i<12; i++){
      if (mip->INODE.i_block[i]){ 
          printf("%d ", mip->INODE.i_block[i]);
          
          get_block(dev, mip->INODE.i_block[i], buf);
          dp = (DIR *)buf;
          cp = buf;
          
          while (cp < buf + BLKSIZE){
            strncpy(temp, dp->name, dp->name_len);
            temp[dp->name_len] = 0;
          
            printf("%s  ", temp);

            cp += dp->rec_len;
            dp = (DIR *)cp;
          }
      }
   }
   printf("\n");

  //  if (ip->i_block[12]){
  //     printf("===============  Indirect blocks   ===============\n"); 
  //  }
  //  get_block(dev,  ip->i_block[12], ibuf);
  //  int x = 0;
  //  while(x < 256)
  //  {
  //         printf("%d " , ibuf[x]);

  //         get_block(dev, mip->INODE.i_block[x], buf);
  //         dp = (DIR *)buf;
  //         cp = buf;
          
  //         while (cp < buf + BLKSIZE){
  //           strncpy(temp, dp->name, dp->name_len);
  //           temp[dp->name_len] = 0;
          
  //           printf("%s  ", temp);

  //           cp += dp->rec_len;
  //           dp = (DIR *)cp;
  //         }
  //     x++;
  //  }

  //  printf("\n");

  //  if (ip->i_block[13]){
  //    printf("===========  Double Indirect blocks   ============\n"); 
  //  }

  //  bzero(ibuf,1024);

  //  get_block(fd,  ip->i_block[13], ibuf);
  //  x = 0;
  //  while(ibuf[x])
  //  {
  //         get_block(dev, mip->INODE.i_block[x], buf);
  //         dp = (DIR *)buf;
  //         cp = buf;
          
  //         while (cp < buf + BLKSIZE){
  //           strncpy(temp, dp->name, dp->name_len);
  //           temp[dp->name_len] = 0;
          
  //           printf("%s  ", temp);

  //           cp += dp->rec_len;
  //           dp = (DIR *)cp;
  //         }
  //     int y = 0;
  //     while(dibuf[y])
  //     {
  //         printf("%d " , dibuf[y]);

  //         get_block(dev, mip->INODE.i_block[x], buf);
  //         dp = (DIR *)buf;
  //         cp = buf;
          
  //         while (cp < buf + BLKSIZE){
  //           strncpy(temp, dp->name, dp->name_len);
  //           temp[dp->name_len] = 0;
          
  //           printf("%s  ", temp);

  //           cp += dp->rec_len;
  //           dp = (DIR *)cp;
  //         }
  //        y++;
  //     }
  //     x++;
  //  }
}

int ls(char * pathname)
{

  //printf("pathname: %s \n", pathname);

  int ino;

  MINODE *mip = running->cwd;

    //breaks path down and places tokens into name array 
  if(strcmp(pathname,"")){
    //if pathname is not empty then tokenize
    tokenize(pathname);
  }
  else{
    //length of name array set to 0
    // printf("mip inode links count: %d", mip->INODE.i_links_count);
    // printf("\n");
    ls_dir(mip);
    return;
  }

  //sets ino and minode pointer to root if starting search from root directroy 
  if(pathname[0] =='/'){
    ino = root->ino;
    mip = root;
  }
  else{
    ino = running->cwd->ino;
  }

  for (int i=0; i<n; i++){
        printf("===========================================\n");
        printf("search name[%d]=%s in ino=%d\n", i, name[i], ino);
        ino = search(mip, name[i]);

        if (ino==0){
           printf("name %s does not exist\n", name[i]);
           return -1;
        }
  } 

  mip = iget(dev, ino);

  ls_file(mip,name);
}

char *pwd(MINODE *wd)
{
  printf("pwd: READ HOW TO pwd in textbook!!!!\n");
  if (wd == root){
    printf("/\n");
    return;
  }
}

#endif