#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <string>

using namespace std;

class Product {
	string productID;																	// ��ǰ ���� ��ȣ
	string productName;																	// ��ǰ��
	string productManufacturer;															// ��ǰ ������
	int productPrice;																	// ��ǰ �Ǹ� ����
	int salePrice;																		// ���� ���Ǵ� ����
	int productStock;																	// ��ǰ ���
	static bool isDiscounted;															// ���� ����
	static float discountRatio;															// ���� ����
public:
	// �������̽� �Լ�
	Product(void);																		// ������
	string getProductID(void) const;													// ��ǰ ��ȣ ���
	void setProductID(void);															// ��ǰ ��ȣ ����
	int getProductPrice(void) const;													// ��ǰ ���� ���
	void setProductPrice(int price);													// ��ǰ ���� ����
	int getProductStock(void) const;													// ��ǰ ��� ���
	void setProductStock(int stock);													// ��ǰ ��� ����
	string getProductName(void) const;													// ��ǰ�� ���
	void setProductName(string& name);													// ��ǰ�� ����
	string getProductManufacturer(void) const;											// ��ǰ ������ ���
	void setProductManufacturer(string& manufacturer);									// ��ǰ ������ ����
	void setSalePrice(void);															// �ǸŵǴ� ���� ����
	int getSalePrice(void) const;														// �ǸŵǴ� ���� ����			
	static void setDiscountRatio(float ratio);											// ���� ���� ����
	static float getDiscountRatio(void);												// ���� ���� ���			
	static void setDiscount(bool discount);												// ���� ���� ����
	static bool getDiscount(void);														// ���� ���� ���

	// ��ǰ ���� �Լ�
	static void checkDisCountDay(tm salesStart, tm salesEnd);							// ���� �Ⱓ �� ���� ���� ����
	static void addProductStock(string id, int cnt);									// ��ǰ ���� �߰�
	static void subProductStock(string id, int cnt);									// ��ǰ ���� ����
	static bool registerProduct(string name, string manufacture, int price, int stock);	// ������ ���̽��� ��ǰ ���
	static bool deleteProduct(string id);												// ������ ���̽����� ��ǰ ����
	static bool checkProductExist(string id);											// ��ǰ ������ ���̽��� �ش��ϴ� ��ǰ�� �ִ��� Ȯ��
};

#endif 