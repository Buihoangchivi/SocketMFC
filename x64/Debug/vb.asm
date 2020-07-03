#doc du lieu tu file

.data
	fin: .asciiz "dethi.txt"
	tb_NhapChu: .asciiz "\tNhap chu kiem tra: "
	tb_NhapKiTu: .asciiz "\tNhap ki tu: "
	tb_NhapTen: .asciiz "\tNhap ten (gom cac ky tu tu A-Z, a-z, 0-9): "
	tb_NhapSai: .asciiz "\tTen khong hop le! Moi ban nhap lai! "
	tb_DoanChu: .asciiz "\n=====Lua Chon======\nNhap 1: Doan ky tu.\nNhap 2: Doan tu.\n\tLua chon: " 
	tb_LuaChonSai: .asciiz "\tLua chon khong ton tai."
	tb_Ten: .asciiz "\tTen cua ban: "
	tb_Diem: .asciiz "\tDiem cua ban la: "
	tb_KetThuc: .asciiz "\n=====Lua Chon======\n1. Choi lai.\n2. Thoat.\n"
	tb_Chon: .asciiz "\tNhap lua chon: "
	tb_ManChoi: .asciiz "\tSo man da choi cua ban la: "
	tb_CamOn: .asciiz "\tCam on ban da tham gia tro choi"
	tb_SoLanDoanSai: .asciiz"\tSo lan doan sai cua ban la: "
	tb_SoChuCaiDoanDung: .asciiz"\tSo chu cai doan dung cua ban la: "
	tb_ThuaCuoc: .asciiz"\tTHUA CUOC"
	tb_DoanDungTu: .asciiz "\tBan da tra loi dung tu khoa"
	tb_DoanSaiTu: .asciiz "\tBan da doan sai tu khoa !!!"
	tb_DoanDungKiTu: .asciiz "\tBan da doan dung ki tu"
	tb_DoanSaiKiTu: .asciiz "\tBan da doan sai ki tu!!!"
	tb_HetDe: .asciiz "Het de!!!"
	tb_KiTuDaNhap: .asciiz "Ki tu da nhap!!! Moi ban nhap lai"
	tb_KetQua: .asciiz "\tTu khoa la: "
	n: .word 0 #So bo de N
	m: .word 0 #Do dai chuoi de
	k: .word 0 #So thu tu cua de
	
	luachon: .word #Lua chon
	diem: .word 0 #Diem cua nguoi choi
	sai: .word 0 #So lan doan sai cua nguoi choi(ki tu)
	dung: .word 0 #So lan doan dung cua nguoi choi(ki tu)
	man: .word 0 #So man da choi
	sode: .word 0 #So de da choi
	sokitu_daco: .word 0 #So ki tu da co trong dap an	

	n_kitu: .word 0 #So ki tu chuoi nhap
	
	str: .space 100000 #Chuoi nhap vao co do dai toi da la 2000 bytes
	ans: .space 100000 #De co do dai toi da la 2000 bytes
	kq: .space 100
	chuoikitu: .space 100
	ten: .space 100
	de_daco: .space 1000
	kitu_daco: .space 1000
	hinh1: .asciiz "\n_______\n|/    |\n|\n|\n|\n|\n|\n|\n|\n"
	hinh2: .asciiz "\n_______\n|/    |\n|     O\n|\n|\n|\n|\n|\n"
	hinh3: .asciiz "\n_______\n|/    |\n|     O\n|     |\n|\n|\n|\n|\n"
	hinh4: .asciiz "\n_______\n|/    |\n|     O\n|    /|\n|\n|\n|\n|\n"
	hinh5: .asciiz "\n_______\n|/    |\n|     O\n|    /|\\\n|\n|\n|\n|\n"
	hinh6: .asciiz "\n_______\n|/    |\n|     O\n|    /|\\\n|    / \n|\n|\n|\n"
	hinh7: .asciiz "\n_______\n|/    |\n|     O\n|    /|\\\n|    / \\\n|\n|\n|\n"
	fout: .asciiz "nguoichoi.txt"
	tb: .asciiz "=========== Top 10 nguoi choi co so diem cao nhat ===========\n\n"
	xd: .asciiz "\n"
	format: .asciiz ". "
	data: .space 100000 #Chuoi du lieu gom cac bo ten, diem, so luot da duoc cap nhat
	#str: .space 100000 #Chuoi lay tu file fout co do dai toi da la 100000 bytes
	temp_str: .space 100 #Bien chuoi tam
	string: .space 100000 #Chuoi lay tu file fout co do dai toi da la 100000 bytes

.text

DocFile:
	#Truyen tham so
	la $a0, str
	la $a1, fin
	
	#Goi ham DocFile
	jal _DocFile
	#truyen tham so
	la $a0,ten

	#Goi hàm NhapTen
	jal _NhapTen

	#xuat tb_Ten
	li $v0,4
	la $a0,tb_Ten
	syscall

	#Xuat ten
	li $v0,4
	la $a0,ten
	syscall
	#Xu ly ten
	la $t0, ten
Loop:
	lb $t1, ($t0)
	beq $t1, $0, Dung
	addi $t0, $t0, 1
	j Loop

Dung:
	subi $t0, $t0, 1
	sb $0, ($t0)

	#Lay ra so luong de
LaySoDe:
	#Truyen tham so
	la $a0, n
	la $a1, str

	#Goi ham LaySoDe
	jal _LaySoDe


 	#Cjoi lai
ChoiLai:
	sw $0, sode
	sw $0, diem
	sw $0, man

	#Tao de moi
TaoDe:
	lw $t0,sode
	lw $t1,n
	beq $t0, $t1, HetDe
	sw $0, dung  
	sw $0, sai
	
	#Lay de 1 cach ngau nhien
LayDeNgauNhien:
	#Luu de da co
	la $t3, de_daco	
	li $t4, 1
	sb $t4, ($t3)
	addi $t3, $t3,1
	
	li $t4, 3
	sb $t4, ($t3)
	addi $t3, $t3,1
	
	li $t4, 5
	sb $t4, ($t3)
	#Random ra vi tri cua de
LayViTriDe:
#Random vi tri de
	lw $s0,n
	li $v0, 42 #random
	move $a1, $s0 #$a0 nhan gia tri random trong doan [0, N - 1]
	syscall
	addi $s2, $a0, 1 #$s2 = $a0 + 1 de $s2 thuoc doan [1, N]
	sw $s2,k 

	
	# Kiem tra
	
	la $a0, de_daco
	lw $a1, k
	lw $a2, sode 
	li $a3, 0 #Tra ve ket qua (0  la co roi, 1 la chua co)
	jal _KiemTraDeTrung
	#Sau khi xong neu chua cho thi se luu vo da co va tang so de len
	beqz $a3, LayViTriDe

	

	#Truyen tham so
	lw $a0, k
	la $a1, str
	la $a2, ans

	#Goi ham LayDeNgauNhien
	jal _LayDeNgauNhien
	

	#Xuong dong:
	li $v0,11
	li $a0,'\n'
	syscall
		


#Dem so luong ki tu de

	la $a0, ans
	lw $a1, m
	jal _DemSoLuong
	sw $a1, m
	
	#Khoi tao kqua *
	
	la $a0, kq
	lw $a1, m
	jal _KhoiTao

	#Xuat ketqua
	li $v0, 4
	la $a0, kq
	syscall

	#Xuong dong:
	li $v0,11
	li $a0,'\n'
	syscall


	#Goi ham doan chu
	la $a0,diem
	la $a1,sai
	la $a2,dung
	la $a3,man
	jal _DoanChu

	#Het de
HetDe:
	sw $0, sode
	#Xuat thong bao het de
	li $v0, 4
	la $a0, tb_HetDe
	syscall

	#Xuong dong:
	li $v0,11
	li $a0,'\n'
	syscall
	
	#Xuat thong bao diem:
	li $v0,4
	la $a0, tb_Diem
	syscall


	lw $t3,diem
	
	li $v0,1
	move $a0,$t3
	syscall

	#Xuong dong:
	li $v0,11
	li $a0,'\n'
	syscall

	j DocFile1

	#Ket thuc tro choi
KetThucTroChoi:

	#Cam on nguoi choi
	li $v0, 4
	la $a0, tb_CamOn
	syscall
	
	
KetThucChuongTrinh:
	#Ket thuc chuong trinh
	li $v0,10
	syscall


#==============================Ham Doc File==============================

#Dau thu tuc
_DocFile:
	addi $sp, $sp, -32
	sw $ra, ($sp)
	sw $s0, 4($sp) #str
	sw $s1, 8($sp) #dia chi file
	sw $s2, 12($sp) #ten file can doc du lieu

	#Lay tham so luu vao thanh ghi
	la $s0, ($a0) #luu dia chi str vao $s0
	la $s2, ($a1) #luu dia chi ten file vao $s2

#Than thu tuc
	#Open file
	li $v0, 13
	move $a0, $s2 #Dia chi cua chuoi chua ten file
	li $a1, 0 #flags: 0 la doc tu file, 1 la viet vao file
	li $a2, 0 #mode is ignored
	syscall
	
	#Luu dia chi file vao $t0
	move $s1, $v0

	#Read file
	li $v0, 14
	move $a0, $s1 #Dua dia chi file vao $a0
	la $a1, ($s0) #str la chuoi luu cac ky tu doc tu file
	li $a2, 100000 #Doc toi da 100000 ky tu vao chuoi str
	syscall

	#Close file
	li $v0, 16
	move $a0, $s1
	syscall

#Cuoi thu tuc
	#Restore
	lw $ra, ($sp)
	lw $ra, ($sp)
	lw $s0, 4($sp) #str
	lw $s1, 8($sp) #dia chi file
	lw $s2, 12($sp) #ten file can doc du lieu

	#Xoa stack
	addi $sp, $sp, 32

	#Tra ve
	jr $ra

#=============================Ham Lay So De=============================

#Dau thu tuc
_LaySoDe:
	addi $sp, $sp, -32
	sw $ra, ($sp)
	sw $s0, 4($sp) #N
	sw $s1, 8($sp) #str
	sw $s2, 12($sp) #Luu tru dia chi N
	sw $t0, 16($sp) #i
	sw $t1, 20($sp)	#bien so sanh
	sw $t2, 24($sp) #str[i]

	#Lay tham so luu vao thanh ghi
	move $s2, $a0 #luu N vao $s2
	move $s1, $a1 #luu str vao $s1

#Than thu tuc
	#Doc so bo de N	
	#Khoi tao cac gia tri
	li $s0, 0 #N = 0
	li $t0, 10 #tam = 10

_LaySoDe.Lap1:
	#Doc str[i] vao $t2
	lb $t2, ($s1)  

	#Neu str[i] = '*' thi dung lai
	beq $t2, '*', _LaySoDe.KetThucLap1

	#Nguoc lai tiep tuc dua str[i] vao N
	mult $s0, $t0 #luu N * 10 vao $lo
	mflo $s0 #N = N * 10
	subi $t2, $t2, '0' #Chuyen ky tu sang so
	add $s0, $s0, $t2 #N = N + str[i]

	#Tang len str[i + 1]
	addi $s1, $s1, 1
	
	#Tiep tuc thuc hien vong lap
	j _LaySoDe.Lap1

_LaySoDe.KetThucLap1:
	sw $s0, ($s2)

#Cuoi thu tuc
	#Restore
	lw $ra, ($sp)
	lw $s0, 4($sp) #N
	lw $s1, 8($sp) #str
	lw $s2, 12($sp) #Luu tru dia chi N
	lw $t0, 16($sp) #i
	lw $t1, 20($sp)	#bien so sanh
	lw $t2, 24($sp) #str[i]

	#Xoa stack
	addi $sp, $sp, 32

	#Tra ve
	jr $ra

#=============================Ham Lay De Ngau Nhien=============================

#Dau thu tuc
_LayDeNgauNhien:
	addi $sp, $sp, -32
	sw $ra, ($sp)
	sw $s0, 4($sp) #k
	sw $s1, 8($sp) #str
	sw $t0, 12($sp) #i
	sw $t1, 16($sp)	#bien so sanh
	sw $t2, 20($sp) #str[i]
	
	#Lay tham so luu vao thanh ghi
	move $s0, $a0 #luu k vao $s0
	move $s1, $a1 #luu str vao $s1

#Than thu tuc

	


_LayDeNgauNhien.Lap1:
	#Doc str[i] vao $t2
	lb $t2, ($s1) 

	#Neu str[i] = '*' thi dung lai
	beq $t2, '*', _LayDeNgauNhien.KetThucLap1

	#Tang len str[i + 1]
	addi $s1, $s1, 1
	
	#Tiep tuc thuc hien vong lap
	j _LayDeNgauNhien.Lap1

_LayDeNgauNhien.KetThucLap1:
	#Khoi tao cac gia tri
	li $t0, 0 #i = 0

_LayDeNgauNhien.Lap2:
	#Doc str[i] vao $t2
	lb $t2, ($s1) 

	#Neu chay den cuoi chuoi str thi dung lai
	beq $t2, $0, _LayDeNgauNhien.KetThucHam

	#Neu str[i] != '*' thi xet tiep ky tu tiep theo
	bne $t2, '*', _LayDeNgauNhien.TiepTuc

	#Neu str[i] = '*' thi tang dem i len 1 va kiem tra
_LayDeNgauNhien.TangDem:
	addi $t0, $t0, 1 #i = i + 1

	#Kiem tra co phai de thu k hay khong
	slt $t1, $t0, $s0 #if (i < k) then tang str[i] len
	beq $t1, 1, _LayDeNgauNhien.TiepTuc

	#Truong hop da chay toi de thu k
	#Xuat phat tai ky tu dau tien cua de thu k
	addi $s1, $s1, 1

	_LayDeNgauNhien.Lap3:
		#Doc str[i] vao $t2
		lb $t2, ($s1) 
	
		#Neu str[i] = '*' hoac cuoi chuoi str thi dung lai
		beq $t2, '*', _LayDeNgauNhien.KetThucHam
		beq $t2, $0, _LayDeNgauNhien.KetThucHam
	
		#Doc str[i] vao $t2
		lb $t2, ($s1)

		#Luu ky tu str[i] vao ans[i]
		sb $t2, ($a2)

		#Tang str va ans len 1
		addi $s1, $s1, 1
		addi $a2, $a2, 1
	
		#Tiep tuc thuc hien vong lap
		j _LayDeNgauNhien.Lap3

_LayDeNgauNhien.TiepTuc:
	#Tang len str[i + 1]
	addi $s1, $s1, 1
	
	#Tiep tuc thuc hien vong lap
	j _LayDeNgauNhien.Lap2

#Cuoi thu tuc
_LayDeNgauNhien.KetThucHam:
	sb $0, ($a2) #Them ky tu ket thuc chuoi '\0' vao cuoi chuoi ans

	
	#Restore
	lw $ra, ($sp)
	lw $s0, 4($sp) #k
	lw $s1, 8($sp) #str
	lw $t0, 12($sp) #i
	lw $t1, 16($sp)	#bien so sanh
	lw $t2, 20($sp) #str[i]

	#Xoa stack
	addi $sp, $sp, 32

	#Tra ve
	jr $ra


#==============================Ham Lay Top 10==============================

#Dau thu tuc
_LayTop10:
	addi $sp, $sp, -16
	sw $ra, ($sp)
	sw $s0, 4($sp) #string
	sw $t0, 8($sp) #char
	sw $t1, 12($sp) #count
	sw $t2, 16($sp) #temp

	#Lay tham so luu vao thanh ghi
	la $s0, ($a0) #luu dia chi string vao $s0

#Than thu tuc
	#Khoi tao cac bien
	li $t1, 1 #count = 1

	#In thong bao xuat top10
	li $v0, 4
	la $a0, tb
	syscall

	#In so 1
	li $v0, 1
	move $a0, $t1
	syscall

	#In thong bao format
	li $v0, 4
	la $a0, format
	syscall

_LayTop10.Loop:
	#Doc phan tu thu i cua string
	lb $t0, ($s0) #char = string[i]
	
	#Neu da cap nhat du lieu thi tiep tuc tang den cuoi chuoi string
	beqz $t0, _LayTop10.EndLoop

	#Kiem tra char co la ky tu '*' hay khong
	li $t2, 42 #temp = '*'
	bne $t0, $t2, _LayTop10.KhongInSTT

	#Kiem tra cuoi chuoi hay chua
	addi $s0, $s0, 1 #string[i + 1]
	#Doc phan tu thu i cua string
	lb $t0, ($s0) #char = string[i]
	#Neu da cap nhat du lieu thi tiep tuc tang den cuoi chuoi string
	beqz $t0, _LayTop10.EndLoop
	#Neu chua het chuoi thi giam ve phan tu ban dau
	addi $s0, $s0, -1 #string[i - 1]

	#In dau xuong dong
	li $v0, 4
	la $a0, xd
	syscall

	#Nguoc lai neu char = '*' thi in ra count
	addi $t1, $t1, 1 #count++
	addi $t2, $0, 11 #temp = 11

	#Neu da in du top 10 thi dung xuat
	beq $t1, $t2, _LayTop10.EndLoop

	#Nguoc lai neu chua du thi in tiep
	#In count
	li $v0, 1
	move $a0, $t1
	syscall

	#In thong bao format
	li $v0, 4
	la $a0, format
	syscall

	#Tang len ky tu tiep theo
	j _LayTop10.TangKyTu

_LayTop10.KhongInSTT:
	#In char ra man hinh
	li $v0, 11
	move $a0, $t0
	syscall

_LayTop10.TangKyTu:
	addi $s0, $s0, 1 #string[i + 1]
	#Tiep tuc thuc hien vong lap
	j _LayTop10.Loop

_LayTop10.EndLoop:

#Cuoi thu tuc
	#Restore
	lw $ra, ($sp)
	lw $s0, 4($sp) #string
	lw $t0, 8($sp) #char
	lw $t1, 12($sp) #count
	lw $t2, 16($sp) #temp

	#Xoa stack
	addi $sp, $sp, 16

	#Tra ve
	jr $ra

#==============================Ham Ghi File==============================

#Dau thu tuc
_GhiFile:
	addi $sp, $sp, -52
	sw $ra, ($sp)
	sw $s0, 4($sp) #name
	sw $s1, 8($sp) #score
	sw $s2, 12($sp) #number
	sw $s3, 16($sp) #dia chi file
	sw $s4, 20($sp) #data
	sw $s5, 24($sp) #string
	sw $t0, 28($sp) #data[i]
	sw $t1, 32($sp) #name[i]
	sw $t2, 36($sp) #i
	sw $t3, 40($sp) #temp
	sw $t4, 44($sp) #count
	sw $t5, 48($sp) #k
	sw $t6, 52($sp) #check

	#Lay tham so luu vao thanh ghi
	la $s0, ($a0) #luu dia chi name vao $s0
	move $s1, $a1 #luu dia chi score vao $s1
	move $s2, $a2 #luu dia chi number vao $s2
	la $s5, ($a3) #luu dia chi name vao $s0

#Than thu tuc
	#Luu dia chi data vao $s4
	la $s4, data
	#Khoi tao check = true
	li $t6, 1

#Khoi tao cac bien
	move $t0, $s4 #data[0]
	move $t1, $s5 #string[0]
	li $t4, 0 #count = 0

_GhiFile.Loop:
	#Doc phan tu thu i cua string
	lb $t3, ($t1) #temp = string[i]
	
	#Neu da cap nhat du lieu thi tiep tuc tang den cuoi chuoi string
	beqz $t6, _GhiFile.Tieptuc2

	li $t2, 45 #i = '-'
	bne $t3, $t2, _GhiFile.Tieptuc1 #Neu temp != '-' thi tiep tuc
	beqz $t4, _GhiFile.BatDau #Neu count = 0 thi xuong bat dau
	#Nguoc lai neu count = 1
	li $t4, 0 #count = 0

	slt $t2, $s1, $t5 #If (score < k) then khong in
	beq $t2, 1, _GhiFile.Tieptuc1

	li $t3, 42 #temp = '*'

_GhiFile.PosFindLoop:
	beq $t0, $s4, _GhiFile.GhiDiemVaoChuoi #Neu score la cao nhat thi them vao dau chuoi
	lb $t2, ($t0) #i = data[i]
	bne $t2, $t3, _GhiFile.TiepTucGiam #Neu chua phai la ky tu '*' thi giam 1 don vi
	#Nguoc lai neu la ky tu '*' thi tang len 1 don vi de xu ly

	addi $t0, $t0, 1 #data[i + 1]
	addi $t1, $t1, 1 #string[i + 1]
	j _GhiFile.GhiDiemVaoChuoi

_GhiFile.TiepTucGiam:
	addi $t0, $t0, -1 #data[i - 1]
	addi $t1, $t1, -1 #string[i - 1]
	j _GhiFile.PosFindLoop

_GhiFile.GhiDiemVaoChuoi:
	
	#Luu name vao data
	#Khoi tao cac bien
	move $t2, $s0 #name[0]

_GhiFile.Loop1:
	lb $t3, ($t2) #temp = name[i]

	#Kiem tra da doc het chuoi name hay chua
	beq $t3, $0, _GhiFile.EndLoop1

	#Truyen du lieu tu name sang data
	sb $t3, ($t0) #data[i] = temp
	
	#Tang gia tri cac bien
	addi $t0, $t0, 1 #data[i + 1]
	addi $t2, $t2, 1 #name[i + 1]

	#Tiep tuc thuc hien vong lap
	j _GhiFile.Loop1

_GhiFile.EndLoop1:
	li $t3, 45 #i = '-'
	sb $t3, ($t0) #data[i] += '-'
	
	#Tang gia tri cac bien
	addi $t0, $t0, 1 #data[i + 1]

	#Luu score vao data
	#Truyen tham so
	move $a0, $t0
	move $a1, $s1
	la $a2, temp_str
	
	#Goi ham DocFile
	jal _GhiSoVaoChuoi

	move $t0, $v0
	
	li $t3, 45 #i = '-'
	sb $t3, ($t0) #data[i] += '-'
	
	#Tang gia tri cac bien
	addi $t0, $t0, 1 #data[i + 1]

	#Luu number vao data
	#Truyen tham so
	move $a0, $t0
	move $a1, $s2
	la $a2, temp_str
	
	#Goi ham GhiSoVaoChuoi
	jal _GhiSoVaoChuoi

	move $t0, $v0

	li $t3, 42 #temp = '*'
	sb $t3, ($t0) #data[i] += '*'
	addi $t0, $t0, 1 #data[i + 1]

	#Danh dau check = false
	li $t6, 0
	lb $t3, ($t1) #temp = string[i]
	j _GhiFile.Tieptuc2

_GhiFile.KhongCapNhat:
	j _GhiFile.Tieptuc1

_GhiFile.BatDau:
	li $t4, 1 #count = 1
	li $t5, 0 #k = 0

_GhiFile.Tieptuc1:
	#Kiem tra da chay con tro toi score chua
	beqz $t4, _GhiFile.Tieptuc2
	beq $t3, $t2, _GhiFile.Tieptuc2 #Neu temp = '-' thi tiep tuc
	#truong hop da xu ly score
	addi $t2, $0, 10 #i = 10
	mult $t5, $t2 #k * 10
	mflo $t5 #k = k * 10
	subi $t2, $t3, 48 #i = string[i] - '0'
	add $t5, $t5, $t2 #k += i
	
_GhiFile.Tieptuc2:
	#Kiem tra da doc het chuoi string hay chua
	bne $t3, $0, _GhiFile.TangChuoi
	beq $t6, $0, _GhiFile.EndLoop
	#Truong hop cap nhat o cuoi chuoi data
	j _GhiFile.GhiDiemVaoChuoi

_GhiFile.TangChuoi:
	#Truyen du lieu tu string sang data
	sb $t3, ($t0) #data[i] = temp
	
	#Tang gia tri cac bien
	addi $t0, $t0, 1 #data[i + 1]
	addi $t1, $t1, 1 #string[i + 1]

	#Tiep tuc thuc hien vong lap
	j _GhiFile.Loop

_GhiFile.EndLoop:
	#Ghi chuoi vao file
	#Open file
	li $v0, 13
	la $a0, fout #Dia chi cua chuoi chua ten file
	li $a1, 1 #flags: 0 la doc tu file, 1 la viet vao file
	li $a2, 0 #mode is ignored
	syscall
	
	#Luu dia chi file vao $s3
	move $s3, $v0

	#Tinh do dai chuoi data
	#Khoi tao gia tri
	move $t0, $s4 #data[0]
	li $t4, 0 #count = 0

_GhiFile.LoopDoDaiChuoi:
	lb $t3, ($t0) #temp = data[count]
	beqz $t3, _GhiFile.EndLoopDoDaiChuoi
	addi $t0, $t0, 1 #data[count + 1]
	addi $t4, $t4, 1 #count++
	j _GhiFile.LoopDoDaiChuoi

_GhiFile.EndLoopDoDaiChuoi:
	#Write file
	li $v0, 15
	move $a0, $s3 #Dua dia chi file vao $a0
	la $a1, ($s4) #str la chuoi luu cac ky tu ghi vao file
	move $a2, $t4
	syscall

	#Close file
	li $v0, 16
	move $a0, $s3
	syscall

#Cuoi thu tuc
	#Restore
	lw $ra, ($sp)
	lw $s0, 4($sp) #name
	lw $s1, 8($sp) #score
	lw $s2, 12($sp) #number
	lw $s3, 16($sp) #dia chi file
	lw $s4, 20($sp) #data
	lw $s5, 24($sp) #string
	lw $t0, 28($sp) #data[i]
	lw $t1, 32($sp) #name[i]
	lw $t2, 36($sp) #i
	lw $t3, 40($sp) #temp
	lw $t4, 44($sp) #count
	lw $t5, 48($sp) #k
	lw $t6, 52($sp) #check

	#Xoa stack
	addi $sp, $sp, 52

	#Tra ve
	jr $ra

#==============================Ham Ghi So Vao Chuoi==============================

#Dau thu tuc
_GhiSoVaoChuoi:
	addi $sp, $sp, -32
	sw $ra, ($sp)
	sw $s0, 4($sp) #str
	sw $s1, 8($sp) #number
	sw $s2, 12($sp) #temp
	sw $t0, 16($sp) #i
	sw $t1, 28($sp) #t

	#Lay tham so luu vao thanh ghi
	la $s0, ($a0) #luu dia chi str vao $s0
	move $s1, $a1 #luu number vao $s1
	la $s2, ($a2) #luu dia chi temp_str vao $s2

#Than thu tuc
	
	#Luu number vao str
	#Luu so dao nguoc cua number vao temp
	#Khoi tao cac bien
	sb $0, ($s2) #temp = '\0'

_GhiSoVaoChuoi.Loop1:
	addi $s2, $s2, 1 #temp[i + 1]
	addi $t0, $0, 10 #i = 10
	div $s1, $t0 #number / 10
	mflo $s1 #number = number / 10
	mfhi $t1 #t = number % 10
	addi $t1, $t1, 48 #t += '0'
	sb $t1, ($s2) #temp[i] = t
	
	#Kiem tra da doc het number hay chua
	bne $s1, $0, _GhiSoVaoChuoi.Loop1

	#Luu temp vao str

_GhiSoVaoChuoi.Loop2:
	lb $t1, ($s2) #t = temp[i]
	sb $t1, ($s0) #str[i] = t

	#Kiem tra da doc het temp hay chua
	beqz $t1, _GhiSoVaoChuoi.KetThucLoop2

	#Tang gia tri cac bien
	addi $s0, $s0, 1 #data[i + 1]
	addi $s2, $s2, -1 #temp[i - 1]

	j _GhiSoVaoChuoi.Loop2
	
_GhiSoVaoChuoi.KetThucLoop2:
	#Tra ve dia chi str
	move $v0, $s0
	
#Cuoi thu tuc
	#Restore
	lw $ra, ($sp)
	lw $s0, 4($sp) #str
	lw $s1, 8($sp) #number
	lw $s2, 12($sp) #temp
	lw $t0, 16($sp) #i
	lw $t1, 28($sp) #t

	#Xoa stack
	addi $sp, $sp, 32

	#Tra ve
	jr $ra



#==============================Ham Nhap Ten==============================
#Dau thu tuc:
_NhapTen:
	addi $sp,$sp,-20
	sw $ra,($sp)
	sw $s0,4($sp) #Luu ten
	sw $t0,8($sp) #Doc 1 ky tu
	sw $t1,12($sp) 
	sw $t2,16($sp) #$t1, $t2, $t3 dung de kiem tra ky tu.
	sw $t3,20($sp) 
	#Lay tham so luu vao thanh ghi
	move $s0,$a0 #Ten
#Than thu tuc:
NhapTen.Loop:
	#xuat tb_nhapten
	li $v0,4
	la $a0,tb_NhapTen
	syscall

	#Nhap 1 chuoi
	li $v0,8
	la $a0,ten
	li $a1,50
	syscall
	
	#luu vao $s0
	la $s0,ten
KiemTraKyTu.Loop:
	#doc 1 ki tu
	lb $t0,($s0)
	#Kiem tra neu ki tu != '\n' thi KiemTraKyTu
	bne $t0,'\n',KiemTraKyTu
	j KetThucNhapTen #Toi ky tu cuoi thi thoat

KiemTraKyTu:
	#Kiem tra la so 
	li $t1,47
	slt $t2,$t1,$t0
	slti $t3,$t0,58
	beq $t2,$t3,KyTuTiep

	#Kiem tra la chu thuong
	li $t1,96
	slt $t2,$t1,$t0
	slti $t3,$t0,123
	beq $t2,$t3,KyTuTiep

	#Kiem tra la chu hoa
	li $t1,64
	slt $t2,$t1,$t0
	slti $t3,$t0,91
	beq $t2,$t3,KyTuTiep
	j NhapSai

KyTuTiep:
	addi $s0,$s0,1 #tang dia chi
	j KiemTraKyTu.Loop

NhapSai:
	#Xuat tb_NhapSai
	li $v0,4
	la $a0,tb_NhapSai
	syscall
	j NhapTen.Loop

KetThucNhapTen:
	
#Cuoi thu tuc:
	#resotore
	lw $ra,($sp)
	lw $s0,4($sp)
	lw $t0,8($sp)
	lw $t1,12($sp) 
	lw $t2,16($sp)
	lw $t3,20($sp)

	#xoa stack
	addi $sp,$sp,20
	# tra ve
	jr $ra

#==============================Ham Kiem Tra Chu In Hoa==============================

_KiemTraChuHoa:
	addi $sp, $sp, -12
	sw $ra, ($sp)
	
	bgeu $a0,65,KiemTraChuHoa_2
KiemTraChuHoa_2:
	bleu $a0, 90,DoiThanhChuThuong
	j _KiemTraChuHoa_Dung
DoiThanhChuThuong:
	addi $a0, $a0, 32
_KiemTraChuHoa_Dung:
	lw $ra, ($sp)
	addi $sp,$sp,12
	jr $ra

_KiemTraChuoiChuHoa:
	addi $sp, $sp, -12
	sw $ra, ($sp)
	sw $s2, 4($sp)
	sw $t1, 8($sp)
	move $s2, $a2
	li $t0,0

_KiemTraChuoiChuHoa.Loop:
	lb $a0,($a1)
	jal _KiemTraChuHoa
	sb $a0, ($a1)

	addi $a1, $a1,1
	addi $t0,$t0,1
	beq $t0,$s2,_KiemTraChuoiChuaHoa.DungLoop
	j _KiemTraChuoiChuHoa.Loop
_KiemTraChuoiChuaHoa.DungLoop:
	lw $ra, ($sp)
	lw $s2, 4($sp)
	lw $t1, 8($sp)
	addi $sp, $sp, -12
	jr $ra	



#==============================Ham Doan Chu==============================
#Dau thu tuc
_DoanChu:
	addi $sp,$sp,-20
	sw $ra,($sp)
	sw $s0,4($sp) #Diem
	sw $s1,8($sp) #Sai
	sw $s2,12($sp) #Dung
	sw $s3,16($sp) 
	sw $t0,20($sp) #Lua chon
	move $s0,$a0
	move $s1,$a1
	move $s2,$a2
	move $s3,$a3
#Than thu tuc:
Menu:
	#Xuat tb_DoanChu
	li $v0,4
	la $a0,tb_DoanChu
	syscall

	#Nhap
	li $v0,5
	syscall
	
	#Luu lua chon vao $s0
	move $t0,$v0
	
	beq $t0,1,NhapKyTu
	beq $t0,2,NhapTu
	j LuaChonSai

NhapKyTu:
	#Xuat thong bao nhap ki tu:
	li $v0,4
	la $a0, tb_NhapKiTu
	syscall

	#Nhap ki tu can kiem tra
	li $v0,12
	syscall
	move $s4,$v0
	
	#Kiem tra chu hoa khong, chu hoa thi doi thanh chu thuong
	move $a0, $s4
	jal _KiemTraChuHoa
	move $s4,$a0
	
	#Xuong dong:
	li $v0,11
	li $a0,'\n'
	syscall
	
	#Kiem tra ki tu nhap chua	
	la $a0,kq
	lw $a1,m
	move $a2, $s4
	li $a3,0
	jal _KiemTraKiTuTrung
	bne $a3, 1,ThongBao_KiTuDaNhap
	
	#Kiem tra ki tu
	la $a0,	ans
	li $a1,0 #Tra ve so luong ki tu
	lw $a2,m
	move $a3,$s4 #Ki tu kiem tra
	jal _KiemTra
	
	#Xuat ketqua
	li $v0, 4
	la $a0, kq
	syscall

	#Xuong dong:
	li $v0,11
	li $a0,'\n'
	syscall

	beq $a1,0,DoanSai
	j DoanDung
ThongBao_KiTuDaNhap:
	li $v0, 4
	la $a0, tb_KiTuDaNhap
	syscall
	
	#Xuong dong:
	li $v0,11
	li $a0,'\n'
	syscall

	j NhapKyTu
DoanSai:
	lw $t0,sai
	add $t0,$t0,1

	sw $t0,($s1)

	#Xuat thong bao doan sai
	li $v0, 4
	la $a0, tb_DoanSaiKiTu
	syscall

	#Xuong dong:
	li $v0,11
	li $a0,'\n'
	syscall

	#Xuat so lan doan sai
	li $v0, 4
	la $a0, tb_SoLanDoanSai
	syscall

	li $v0,1
	move $a0,$t0
	syscall
	
	#Ve hinh
	jal _SoLanSai

	#Xuong dong:
	li $v0,11
	li $a0,'\n'
	syscall
	
	li $t1,7
	beq $t0,$t1,ThuaCuoc

	j Menu
DoanDung:
	lw $t1,dung
	add $t1,$t1,$a1

	sw $t1,($s2)

	
	#Xuat thong bao doan dung
	li $v0, 4
	la $a0, tb_DoanDungKiTu
	syscall

	#Xuong dong:
	li $v0,11
	li $a0,'\n'
	syscall

	#Xuat so chu cai doan dung
	li $v0, 4
	la $a0, tb_SoChuCaiDoanDung
	syscall

	li $v0,1
	move $a0,$t1
	syscall

	#Xuong dong:
	li $v0,11
	li $a0,'\n'
	syscall
	lw $t2,m
	beq $t1,$t2,ThangCuoc

	j Menu
NhapTu:
	#Xuat thong bao nhap chu
	li $v0, 4
	la $a0, tb_NhapChu
	syscall

	#Nhap chuoi ki tu
	li $v0, 8
	la $a0,chuoikitu
	li $a1,100
	syscall

	la $a0,chuoikitu
	lw $a1,n_kitu
	jal _DemSoLuong
	sw $a1,n_kitu
	
	#Kiem tra do dai 2 cai bang nhau khong
	lw $t0,m
	lw $t1,n_kitu
	bne $t0,$t1, ThuaCuoc

	#Kiem tra chuoi co ki tu in hoa khong, co thi doi lai ki tu thuong
	la $a1,chuoikitu
	lw $a2, n_kitu
	jal _KiemTraChuoiChuHoa

	#Kiem tra toan bo	
	la $a0, ans
	lw $a1,m
	la $a2, chuoikitu 
	li $a3, 0 #Tra ve ket qua dung sai
	jal _KiemTraToanBo
	
	
	beq $a3,1,ThangCuoc
	j ThuaCuoc


ThangCuoc:	

	#Xuat thong bao doan dung tu
	li $v0, 4
	la $a0, tb_DoanDungTu
	syscall

	#Xuong dong:
	li $v0,11
	li $a0,'\n'
	syscall

	#Xuat thong bao diem:
	li $v0,4
	la $a0, tb_Diem
	syscall

	lw $t3,diem
	lw $a3,m
	add $t3,$t3,$a3

	sw $t3,($s0)
	
	lw $t4,man
	addi $t4,$t4,1
	sw $t4,man
	
	li $v0,1
	move $a0,$t3
	syscall

	#Xuong dong:
	li $v0,11
	li $a0,'\n'
	syscall
	j TaoDe
ThuaCuoc:
	li $v0,4
	la $a0,hinh7
	syscall

	#Xuat thong bao doan sai tu
	li $v0, 4
	la $a0, tb_DoanSaiTu
	syscall

	#Xuong dong:
	li $v0,11
	li $a0,'\n'
	syscall

	#Xuat thong bao tu khoa chinh xac:
	li $v0, 4
	la $a0, tb_KetQua
	syscall

	#Xuat tu khoa
	li $v0, 4
	la $a0, ans
	syscall

	#Xuong dong:
	li $v0,11
	li $a0,'\n'
	syscall
	#Xuat thong bao thua cuoc:
	li $v0, 4
	la $a0, tb_ThuaCuoc
	syscall

	#Xuong dong:
	li $v0,11
	li $a0,'\n'
	syscall

	#Xuat thong bao diem:
	li $v0,4
	la $a0, tb_Diem
	syscall

	lw $t3,diem
	
	li $v0,1
	move $a0,$t3
	syscall

	#Xuong dong:
	li $v0,11
	li $a0,'\n'
	syscall

	#So man da choi
	li $v0, 4
	la $a0, tb_ManChoi
	syscall

	li $v0,1
	lw $t0,man
	move $a0,$t0	
	syscall

	#Xuong dong:
	li $v0,11
	li $a0,'\n'
	syscall


	j ThuaTroChoi
LuaChonSai:
	#Xuat tb_LuaChonSai
	li $v0,4
	la $a0,tb_LuaChonSai
	syscall

	j Menu

	lw $ra,($sp)
	lw $s0,4($sp) #Diem
	lw $s1,8($sp) #Diem
	lw $s2,12($sp) #Diem
	lw $s3,16($sp) 
	lw $t0,20($sp) #Lua chon

	addi $sp,$sp,20
	jr $ra


#==============================Ham Dem So Luong Ki Tu==============================
_DemSoLuong:
	addi $sp,$sp,-12
	sw $ra, ($sp)
	sw $s0, 4($sp) #de
	sw $t0, 12($sp) #Bien lap
	sw $t1, 16($sp) #Bien so sanh
	sw $t2,20 ($sp) #Dem

	move $s0,$a0
	#Khoi tao vong lap
	li $t0,0
	
_DemSoLuong.Loop:
	lb $t1, ($s0)
	bne $t1,'\0',KiemTra_$t1
	j End_Loop
KiemTra_$t1:
	beq $t1,'\n',End_Loop
	j TangDem
TangDem:
	addi $t0,$t0,1
	addi $s0,$s0,1
	addi $t2,$t2,1
	j _DemSoLuong.Loop
End_Loop:
	move $a1, $t0
	#resotore
	lw $ra, ($sp)
	lw $s0, 4($sp) #de
	lw $t0, 12($sp) #Bien lap
	lw $t1, 16($sp) #Bien so sanh
	lw $t2,20 ($sp) #Dem

	#xoa stack
	addi $sp,$sp,12
	# tra ve
	jr $ra

#==============================Ham Khoi Tao Ket Qua==============================

_KhoiTao:
	addi $sp,$sp, -16
	sw $ra, ($sp)
	sw $s0, 4($sp) 
	sw $s1, 8($sp)
	sw $t0, 12($sp) #bien dem
	sw $t2, 16($sp) #Luu ki tu *	
	
	move $s0,$a0
	move $s1,$a1
	li $t0,0
_KhoiTao.Loop:
	li $t2, '*'
	sb $t2,($s0)
	addi $t0,$t0,1
	addi $s0,$s0,1
	beq $t0,$s1,_KhoiTao.DungLoop
	j _KhoiTao.Loop
_KhoiTao.DungLoop:

	sb $0, ($s0)

	lw $ra, ($sp)
	lw $s0, 4($sp) 
	lw $s1, 8($sp)
	lw $t0, 12($sp) #bien dem
	lw $t2, 16($sp) #Luu ki tu *	
	addi $sp,$sp,16
	
	jr $ra

#==============================Ham Kiem Tra Chuoi Nhap Vao==============================
_KiemTra:
	addi $sp,$sp -32
	sw $ra,($sp)
	sw $s0,4($sp)	#Luu de
	sw $s1,8($sp)	#Luu so luong nhap ki tu co trong de
	sw $s2,12($sp)	#Luu n
	sw $s3,16($sp)	#Luu ki tu nhap
	sw $t0, 20($sp) #Bien dem lap
	sw $t1, 24($sp) #Lay gia tri tai vi tri i cua de
	sw $t2, 28($sp) #Luu ket qua
	
	li $t0,0
	la $t2,kq

	move $s0,$a0
	move $s1,$a1
	move $s2, $a2
	move $s3, $a3
_KiemTra.Loop:
	lb $t1, ($s0)
	beq $t1,$s3,_KiemTra.Tang
	j _KiemTra.ktlap
_KiemTra.Tang:
	addi $s1,$s1,1
	sb $s3,($t2)
	j _KiemTra.ktlap
_KiemTra.ktlap:
	addi $t0,$t0,1
	addi $t2,$t2,1
	addi $s0,$s0,1
	blt $t0,$s2,_KiemTra.Loop
	
	move $a1,$s1
	lw $ra,($sp)
	lw $s0,4($sp)	
	lw $s1,8($sp)
	lw $s2,12($sp)
	lw $s3,16($sp)
	lw $t0, 20($sp) #Bien dem lap
	lw $t1, 24($sp) #Lay gia tri tai vi tri i cua de
	lw $t2, 28($sp) #Luu ket qua
	
	addi $sp, $sp,32
	jr $ra	
_KiemTraToanBo:
	addi $sp, $sp,-32
	sw $ra,($sp)
	sw $s0,4($sp) #Luu de
	sw $s1,8($sp) #luu n
	sw $s2,12($sp) #luu chuoi ki tu
	sw $s3,16($sp) #tra ve ket qua
	sw $t0, 20($sp) #Bien dem lap
	sw $t1, 24($sp) #Lay gia tri tai vi tri i cua de
	sw $t2, 28($sp) #Luu gia tri tai vi tri i cua chuoi

	move $s0,$a0
	move $s1,$a1
	move $s2,$a2
	move $s3,$a3
	li $t0,0

_KiemTraToanBo.Loop:
	lb $t1,($s0)
	lb $t2,($s2)
	beq $t1, $t2, _KiemTraToanBo.TangDem
	j _KiemTraToanBo.EndLoop
_KiemTraToanBo.TangDem:
	addi $t0,$t0,1
	addi, $s0, $s0,1
	addi, $s2, $s2,1
	blt $t0,$s1,_KiemTraToanBo.Loop
	j _KiemTraToanBo.EndLoop
_KiemTraToanBo.EndLoop:		
	beq $t0,$s1,_KiemTraToanBo.GanDung
	li $s3,0
	j _KiemTraToanBo.TraVe
_KiemTraToanBo.GanDung:
	li $s3,1
_KiemTraToanBo.TraVe:
	move $a3,$s3


	lw $ra,($sp)
	lw $s0,4($sp)	
	lw $s1,8($sp)
	lw $s2,12($sp)
	lw $s3,16($sp)
	lw $t0, 20($sp)
	lw $t1, 24($sp)
	lw $t2, 28($sp)
	
	addi $sp, $sp,32
	jr $ra	

_KiemTraKiTuTrung:
	addi $sp, $sp, -32
	sw $ra, ($sp)
	sw $s0, 4($sp) #Mang ki tu da co
	sw $s1, 8($sp) #So luong ki tu da co
	sw $s2, 12($sp) #Ki tu nhap
	sw $t0,20($sp) #bien lap
	sw $t1,24($sp) # luu gia tri mang	

	li $t0,0 #Khoi tao bien lap
	move $s0,$a0
	move $s1, $a1
	move $s2, $a2
	
	j KiemTraKiTu.Loop
KiemTraKiTu.Loop:
	lb $t1, ($s0)
	beq $t1, $s2,EndLoop_KiemTra
	
	addi $t0,$t0,1
	addi $s0,$s0,1
	blt $t0,$s1,KiemTraKiTu.Loop
	
	li $a3,1
EndLoop_KiemTra:
	lw $ra, ($sp)
	lw $s0, 4($sp)
	lw $s1, 8($sp) 
	lw $s2, 12($sp)
	lw $s3, 16($sp)
	lw $t0,20($sp) #bien lap
	lw $t1, 24($sp) #Luu gia tri cua mang
	addi $sp, $sp, +32
	
	jr $ra

_KiemTraDeTrung:
	addi $sp, $sp, -32
	sw $ra, ($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp) 
	sw $s2, 12($sp)
	sw $t0,20($sp) #bien lap
	sw $t1,24($sp) #Luu gi tri cua mang	

	li $t0,0
	move $s0,$a0
	move $s1, $a1
	move $s2, $a2
	addi $s0,$s0,4
	
	beqz $s2, Luuvaode
	j KiemTra.Loop
KiemTra.Loop:
	lw $t1, ($s0)
	beq $t1, $s1,EndLoop
	
	addi $t0,$t0,1
	addi $s0,$s0,4
	blt $t0,$s2,KiemTra.Loop
	j Luuvaode
Luuvaode:
	addi $s2, $s2,1
	
	li $a3,1
	sw $s1, ($s0)
	sw $s2, sode
EndLoop:
	lw $ra, ($sp)
	lw $s0, 4($sp)
	lw $s1, 8($sp) 
	lw $s2, 12($sp)
	lw $s3, 16($sp)
	lw $t0,20($sp) #bien lap
	lw $t1,24($sp)
	addi $sp, $sp, +32
	
	jr $ra

#==============================Ham Ve Hinh==============================
#In ra hinh
_SoLanSai:
	
	addi $sp,$sp,-32
	sw $ra,($sp)
	sw $s0,4($sp)
	sw $t1,8($sp)

	
	lw $t1,sai	#truyen tham so vao
	beq $t1,1,SaiLan1
	beq $t1,2,SaiLan2
	beq $t1,3,SaiLan3
	beq $t1,4,SaiLan4
	beq $t1,5,SaiLan5
	beq $t1,6,SaiLan6
	#beq $t1,7,SaiLan7

Return:
	
	lw $ra,($sp)
	lw $s0,4($sp)
	lw $t1,8($sp)
	addi $sp,$sp,32
	jr $ra
	
SaiLan1:
	li $v0,4
	la $a0,hinh1
	syscall
	
	j Return
SaiLan2:
	li $v0,4
	la $a0,hinh2
	syscall
	j Return
SaiLan3:
	li $v0,4
	la $a0,hinh3
	syscall

	j Return
SaiLan4:
	li $v0,4
	la $a0,hinh4
	syscall

	j Return
SaiLan5:
	li $v0,4
	la $a0,hinh5
	syscall

	j Return
SaiLan6:
	li $v0,4
	la $a0,hinh6
	syscall
	
	j Return
SaiLan7:
	li $v0,4
	la $a0,hinh7
	syscall

	j Return
ThuaTroChoi:

	

	#Doc file ghi vao output
DocFile1:
	#Truyen tham so
	la $a0, string
	la $a1, fout
	
	#Goi ham DocFile
	jal _DocFile

	#Ghi file
GhiFile:
	#Truyen tham so
	la $a0, ten
	lw $a1, diem
	lw $a2, man
	la $a3, string
	
	#Goi ham GhiFile
	jal _GhiFile
	
	#Lay ra Top 10 nguoi choi co diem cao nhat
LayTop10:
	#Doc file sau khi da cap nhat
	#Truyen tham so
	la $a0, string
	la $a1, fout
	
	#Goi ham DocFile
	jal _DocFile

	#Truyen tham so
	la $a0, string
	
	#Goi ham LayTop10
	jal _LayTop10


	#Xuat thong bao ket thuc tro choi:
	li $v0, 4
	la $a0, tb_KetThuc
	syscall

	#Xuat thong bao nhap lua chon:
	li $v0, 4
	la $a0, tb_Chon
	syscall

	#Nhap lua chon:
	li $v0,5
	syscall

	

	#Luu lua chon vao $t3
	move $t3,$v0

	beq $t3,1,ChoiLai
	beq $t3,2, KetThucTroChoi

