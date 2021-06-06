# OOP_Project3

物件導向程式設計_Project3_PTT

:::info
Github連結：https://github.com/orertrr/OOP_Project3

目前裡面沒什麼好看的，只是預計做完之後要上傳上去而已
:::


## 物件

- BoardManager
- Viewer
    - LoginViewer
    - BoardTypeViewer
    - BoardViewer
    - PostViewer
    - MailViewer

- Data
    - User
    - Board
    - BoardType
    - Post
    - Commant
    - Mail

### BoardManager

管理所有物件並且接收鍵盤指令將其發送到目前所在的viewer

#### Member Variable

- vector<User\*> users
- vector<Board\*> boards
- vector<BoardType\*> boardtypes
- vector<Mail\*> mails
- User\* currentUser
- vector<Viewer\*> viewers

#### Member Function

- void Start() **進行初始化，啟動迴圈接收鍵盤指令**
- void Send(char key, Viewer\* currentViewer) **將鍵盤指令傳送到currentViewer**
- void Forward() **下一頁**
- void Back() **上一頁**

### Viewer

#### Member Function

- void print() **印出畫面**

#### Child Class

繼承此 Class 的 Child Class 各自實作需要在頁面上執行的 Function

- HomeViewer
- BoardTypeViewer
- BoardViewer
- PostViewer
- MailViewer

### Data

此處為負責資料處理的 Class，擁有各自的資料欄位作為 Member Variable，由於彼此的資料欄位不同，因此要各自實作**新增、刪除、修改、查詢**的Function

**為方便資料儲存和讀取，在文字檔中可嘗試使用'\t'等特殊字元將每個資料欄位分開**

- User
    - int UserID
    - string Account
    - string Password
    - int Permission_Level
- Board
    - int BoardID
    - string BoardName
    - int TypeID **此資料欄位紀錄此看板的分類**
- BoardType
    - int TypeID
    - string Name
- Post
    - int 
    - int UserID **建立此貼文的使用者**
    - int BoardID **此貼文所屬的看板**
    - string Title
    - string Content
- Comment
    - int CommentID
    - int UserID **此資料欄位紀錄建立這則留言的使用者**
    - string content
    - int Kind **此資料欄位紀錄此留言屬於推(Push)、噓(Pull)或兩者皆非(None)**
    - string Delete **此資料欄位紀錄管理員刪除此留言的原因**
- Mail
    - int MailID
    - int FromUserID **寄件人**
    - int ToUserID **收件人**
    - string content

