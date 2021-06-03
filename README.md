# OOP_Project3

物件導向程式設計_Project3_PTT

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

- User
- Board
- BoardType
- Post
- Commant
- Mail

