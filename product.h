#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <string>

using namespace std;

class Product {
	string productID;																	// 상품 고유 번호
	string productName;																	// 상품명
	string productManufacturer;															// 상품 제조사
	int productPrice;																	// 상품 판매 가격
	int salePrice;																		// 실제 계산되는 가격
	int productStock;																	// 상품 재고
	static bool isDiscounted;															// 할인 여부
	static float discountRatio;															// 할인 비율
public:
	// 인터페이스 함수
	Product(void);																		// 생성자
	string getProductID(void) const;													// 상품 번호 출력
	void setProductID(void);															// 상품 번호 설정
	int getProductPrice(void) const;													// 상품 가격 출력
	void setProductPrice(int price);													// 상품 가격 설정
	int getProductStock(void) const;													// 상품 재고 출력
	void setProductStock(int stock);													// 상품 재고 설정
	string getProductName(void) const;													// 상품명 출력
	void setProductName(string& name);													// 상품명 설정
	string getProductManufacturer(void) const;											// 상품 제조사 출력
	void setProductManufacturer(string& manufacturer);									// 상품 제조사 설정
	void setSalePrice(void);															// 판매되는 가격 설정
	int getSalePrice(void) const;														// 판매되는 가격 설정			
	static void setDiscountRatio(float ratio);											// 할인 비율 설정
	static float getDiscountRatio(void);												// 할인 비율 출력			
	static void setDiscount(bool discount);												// 할인 여부 설정
	static bool getDiscount(void);														// 할인 여부 출력

	// 상품 관리 함수
	static void checkDisCountDay(tm salesStart, tm salesEnd);							// 세일 기간 중 할인 가격 설정
	static void addProductStock(string id, int cnt);									// 상품 갯수 추가
	static void subProductStock(string id, int cnt);									// 상품 갯수 차감
	static bool registerProduct(string name, string manufacture, int price, int stock);	// 데이터 베이스에 상품 등록
	static bool deleteProduct(string id);												// 데이터 베이스에서 상품 삭제
	static bool checkProductExist(string id);											// 상품 데이터 베이스에 해당하는 제품이 있는지 확인
};

#endif 