 
 # Ký hiệu O lớn

dùng để mô tả hành vi thuật toán (ví dụ, về mặt thời gian tính toán hoặc lượng bộ nhớ cần dùng) khi kích thước dữ liệu thay đổi


# DS tuyến tính

## Array

- một tập hợp các phần tử của cùng một kiểu dữ liệu
- kích thước của mảng được chỉ định tại thời điểm khai báo nên cố định, là 1 khối ô nhớ liền kề

- Truy cập: O(1)
- Insert/delete ở giữa O(n) do dời các ô nhớ về sau (insert)/về trước (delete)
- insert/delete last O(1)

## Stack
LIFO (vào sau ra trước)

- push: thêm đầu stack
    + kiểm tra full pointer = size - 1
    + gán giá trị vào pointer, pointer++
- pop: xóa đầu stack
    + kiểm tra rỗng pointer == -1
    + trả về giá trị ở pointer, pointer--

- ứng dụng trong gỡ đệ qui

- dslk: 
    + k có trường hợp đầy
    + rỗng khi pointer = null
    + thao tác trên first

## Queue
FIFO (vào trc ra trc)
tổ chức bằng ds tuyến tính hoặc dslk

- enqueue: thêm cuối hàng
- dequeue: xóa đầu hàng

- Front, rear: xem phần tử ở vị trí đầu/cuối

- queue bị tràn

- queue đầy: rear ở ngay trước front (rear + 1 % size = front)

- queue trống: rear = -1 hoặc front = -1

- Khởi tạo: rear = front = -1
- thêm:
    + kiểm tra full
    + kiểm tra rỗng, đúng thì gán rear = front = 0, gán giá trị vào rear
    + k rỗng: gán rear = (rear + 1) % size, gán giá trị vào rear
- xóa:
    + kiểm tra rỗng
    + nếu front = rear (queue có 1 phần tử) đặt front = rear = -1
    + k thì dịch front lên, front = (front + 1) % size 

- tổ chức theo dslk thì k đầy/tràn
    + xóa: kiểm tra rỗng
    + enqueue: insert last
    + dequeue: delete first


# DS Liên kết

- bao gồm các node trong đó mỗi node gồm thuộc tính dữ liệu và địa chỉ đến node tiếp theo trong danh sách
- là cấu trúc động, cấp phát và xóa bộ nhớ khi ct đang chạy

Các phép toán:
    - kiểm tra ds rỗng
    - Search O(n)
    - sort: selection sort O(n^2)

## Đơn
- node có 2 field: data, next
- last node có next = null

- Các phép toán:
    + duyệt xuôi
    + insert/delete after, first

## Kép
- node có 3 field: data, next, prev
- first có prev là null, last có next = null

- Các phép toán:
    + duyệt xuôi, ngược
    + insert before, after, first
    + delete node

## Vòng
- có thể là ds đơn hoặc kép
- node cuối có next = first
- khi chỉ có 1 nút, first.next = first

- Các phép toán:
    + duyệt xuôi
    + insert first, last,

- delete first:
    - nếu ds có 1 node, xóa first
    1. khai báo temp = first, duyệt tới node cuối
    2. gán node cuối next = first->next, first = first->next
    3. xóa temp

- delete last:
    1. Nếu ds có 1 node first.next = first, nếu đúng thì xóa first
    2. khai báo 2 biến current, prev, duyệt tới node cuối
    3. prev.next = current.next (node cuối mới trỏ về first), xóa current



## So sánh
- ds đơn chỉ có phần tử first, kép có first và last
- Node ds đơn chiếm ít bộ nhớ hơn node ds kép vì chỉ có 2 field data và next

- Truy cập các node của DS đơn k hiệu quả so với ds kép vì chỉ duyệt đc 1 chiều

- update cần tính tới
    + đơn: chỉnh sửa next
    + kép: chỉnh prev và next

- các thao tác
    + tìm kiếm: O(n)

- Duyệt: có thể duyệt dslk vòng bắt đầu ở mọi node

### So sánh với array:

- array chỉ chứa dữ liệu, dslk còn chứa dữ liệu và thông tin node tiếp theo

- Kích thước:
    + kích thước của mảng được chỉ định tại thời điểm khai báo nên cố định, là 1 khối ô nhớ liền kề
    + dslk: dữ liệu không được lưu trữ trong một khối và không có kích thước cố định. Thay vào đó, nó bao gồm nhiều khối bộ nhớ ở các địa chỉ khác nhau.


- Thao tác:
    + truy cập: array O(1), dslk O(n): k truy cập phần tử ngẫu nhiên trong dslk nhanh đc
    + tìm kiếm: O(n)
    + insert/delete first: array O(n), dslk O(1)
    + xóa hay thêm phần tử trong dslk không dời các phần tử đi như trong array mà chỉ việc chỉnh lại biến next tại node đang thao tác
        array: O(n), dslk O(n)


# Cây nhị phân tìm kiếm BST

Cây là tập hợp các phần tử gọi là node

- 1 node cũng có thể là cây
- Các nút được gọi là ở cùng một cây khi có đường đi
- Một cây sẽ bao gồm một nút gốc (Root) và m cây con, trong mỗi cây con lại có một nút gốc và m1 cây con nhỏ hơn
- cây không có nút gọi là cây rỗng

- node cha, con

- bậc của node là số cây con, của cây là max số bậc của node
    BST có bậc = 2, số nút con tối đa = 2

- level của node:
    root có level 1

- BT đúng: root và tất cả node trung gian đều có bậc 2, số node = 2 * số node lá - 1

- BT đầy: là BT đúng, all node có số node tối đa, số node = 2^n - 1

- BST: mọi node thì khóa 1 node bất kỳ > khóa các node bên trái, < khóa các node bên phải

- AVL: BST chiều cao cây con bên trái k chênh lệch hơn chiều cao cây bên phải 1

- BST cân bằng hoàn toàn: số node của cây con bên trái k hơn kém hơn số node cây bên phải quá 1

- duyệt cây:
    1. NLR pre order
    2. LNR in order
    3. LRN post order
    4. Theo mức: duyệt từ thấp đến cao, trong mức duyệt từ trái qua phải
    dùng queue để giữ các node
        1. đưa root vào queue
        2. lấy 1 node ra khỏi queue, xử lý, đưa các node con vào queue
        3. lặp cho đến khi queue rỗng

    luôn xử lý node gốc trước, do đưa 2 nút con vào queue theo thứ tự trái sang phải nên khi lấy queue sẽ xử lý đc các node trong cùng mức theo trái qua phải

- các phép toán:
    - tạo cây: root
    - cập nhật

        1. kiểm tra rỗng
        2. giải phóng vùng nhớ
        2. thêm, xóa node
        3. tìm kiếm

## Cây nhị phân cân bằng AVL
- là BST mà tại tất cả các node, chiều cao của cây con bên trái và bên phải k chênh lệch nhau quá 1
- insert/delete 1 node trên cây có thể làm cây mất cân bằng, khi đó phải cân bằng lại cây. Việc cân bằng trên cây AVL chỉ xảy ra ở phạm vi cục bộ bằng cách xoay trái hoặc xoay phải ở một vài nhánh cây con nên sẽ giảm thiểu chi phí cân bằng

- chỉ số cân bằng:
    + bf = 0: cân bằng
    + bf > 1: lệch trái
    + bf < -1: lệch phải

- Tìm kiếm

- Thêm node
    + thêm như BST
    + tính chỉ số cân bằng của các node bị ảnh hưởng
    + nếu mất cân bằng -> cân bằng

    trường hợp thêm vào trái khi bf = 1

- Xóa node


# Sắp xếp

- sắp xếp nội: tất cả dữ liệu đc đưa trong bộ nhớ
- sắp xếp ngoại: dữ liệu nhiều, phải lưu trong các đĩa hoặc file, mỗi lần sort phải đưa 1 phần vào bộ nhớ để sort

1. ## Insertion sort O(n^2)
nếu trong danh sách đã có i-1 phần tử trước đã có thứ tự,
tiếp tục so sánh phần tử a[i] với i-1 phần tử này để tìm vị trí thích hợp cho a[i] xen vào.
Vì danh sách có một phần tử thì tự nó đã có thứ tự, do đó ta chỉ cần so sánh từ phần tử thứ 2 cho đến phần tử thứ n

    1. đánh dấu phần tử đầu tiên là đã sắp xếp
    2. cho mỗi phần tử không được sắp xếp X, lấy phần tử X
    3. for j từ = lastSortedIndex xuống 0
        nếu phần tử hiện tại j > X dịch phần tử đã sắp xếp sang phải 1
        nếu k thì vòng lặp ngắt và chèn X vào

2. ## Selection sort O(n^2)
    1. so sánh tất cả các phần tử của danh sách để chọn phần tử nhỏ nhất đưa về đầu danh sách
    2. chọn phần tử nhỏ nhất trong các phần tử còn lại để đưa về phần tử thứ hai trong danh sách
    3. lặp lại cho đến khi chọn ra được phần tử nhỏ thứ (n-1)

3. ## Bubble sort O(n^2)
    1. duyệt dãy, nếu a[i - 1] > a[i] thì swap
    2. lặp lại cho đến khi k còn đổi chỗ

4. ## Quick sort O(nlogn)
    1. Chọn một phần tử bất kỳ trong danh sách làm điểm chốt x
    2. so sánh và đổi chỗ những phần tử trong danh sách này để tạo ra 2 ds con: ds có giá trị nhỏ hơn x và ds có giá trị lớn hơn x
    3. lặp lại cho 2 ds như trên
    4. kết thúc khi mỗi ds con chỉ còn lại một phần tử

5. ## Merge sort

6. ## Heap sort

Heap là cây nhị phân gần đầy được cài đặt bằng
mảng một chiều với các nút trên Heap có nội dung lớn hơn hay bằng nội dung của các nút con của nó.

# Tìm kiếm

## Tìm kiếm nhị phân O(logn)

- dùng đệ qui

# Đồ thị

- node
- cạnh: nối 2 đỉnh vô hướng
- cung: đc xác định bởi 2 node đỉnh (bắt đầu) và ngọn (kết thúc)
    + khuyên: cạnh nối tới chính nó
- bậc: số cung liên kết tới nút
    + = bậc vào (số ngọn) + bậc ra (số đỉnh)
- 

## Tổ chức data

- Ma trận kề (mảng 2 chiều)
- Ds kề (mảng 1 chiều và dslk)

## Duyệt

1. ## Depth first search (theo chiều sâu)

-
- dùng stack

2. ## Breadth first search (theo chiều rộng)
- duyệt V và tất cả các nút liền kề W của V
- tiếp tục duyệt các node kề của các W
- dùng queue


