/*#include "Main.h"

#define INT_SIZE 4

int e(char *vars, char *password, int passwordLength) {
	int passwordOffset, result;
	passwordOffset = result = 0;

	for (int offset = 0; vars; offset++, vars++) {
		result ^= offset;
		for (size_t i = 0; INT_SIZE; i++, passwordOffset) {
			size_t var = i * 8;
			result ^= (int)password[passwordOffset] << var;
			result ^= (int)(*vars) << var;
		}
	}

	return result;
}

void d(int var, char *vars, int varsLength, char *password, int passwordLength) {
	int passwordOffset, result;
	passwordOffset = result = 0;
	vars = new char[varsLength];

	for (size_t offset = varsLength - 1; ; offset++) {


		if (offset == 0) {
			break;
		}
	}
}*/

#include <iostream>

#include <fstream>
#include <filesystem>

using namespace std;
using namespace experimental::filesystem;

typedef char byte;
#define BYTE_SIZE CHAR_BIT
#define BYTE_SIZE_MARGIN 7
#define BYTE_MAX CHAR_MAX
#define BYTE_MIN CHAR_MIN

byte XXOR(byte var1, byte var2) {
	byte var3 = 0;
	byte bits1[BYTE_SIZE], bits2[BYTE_SIZE];

	for (int i = 0; i < BYTE_SIZE; i++) {
		bits1[i] = ((var1 << (BYTE_SIZE_MARGIN - i)) >> BYTE_SIZE_MARGIN) & 1;
		bits2[i] = ((var2 << (BYTE_SIZE_MARGIN - i)) >> BYTE_SIZE_MARGIN) & 1;
	}

	for (int i = 0; i < BYTE_SIZE; i += 2) {
		var3 |= (bits1[i] != bits2[i + 1]) << (i + 1);
		var3 |= (bits1[i + 1] != bits2[i]) << i;
	}

	return var3;
}

byte mix(byte var1, byte var2) {
	return XXOR(var1, XXOR(var1, var2));
}

bool predict(byte var3, byte *var1, byte *var2) {
	for (byte _var1 = BYTE_MIN; _var1 < BYTE_MAX; _var1++) {
		byte _var2 = XXOR(_var1, var3);
		byte var4 = XXOR(_var2, _var1);

		if (XXOR(var3, var4) == 0) {
			*var1 = _var1;
			*var2 = _var2;
			//return true;
		}
	}

	return false;
}

bool unmix(byte var3, byte *var1, byte *var2) {
	for (byte _var1 = BYTE_MIN; _var1 < BYTE_MAX; _var1++) {
		byte _var3 = XXOR(_var1, var3);
		byte _var2 = XXOR(_var1, _var3);
		byte var4 = XXOR(_var2, _var1);

		if (XXOR(_var3, var4) == 0) {
			*var1 = _var1;
			*var2 = _var2;
			//return true;
		}
	}

	return false;
}

int main(int argc, char *argv[]) {
	/*for (int i = 1; i < argc; i++) {
		char *path = argv[i];
		if (!exists(path)) {
			continue;
		}

		ifstream is(path, ios::binary);

		is.close();
	}*/

	/*byte a = 172;
	byte b = 69;
	byte c = XXOR(a, b);
	byte d = XXOR(b, a);

	byte ac = XXOR(a, c);
	byte bc = XXOR(b, c);
	byte ca = XXOR(c, a);
	byte cb = XXOR(c, b);
	byte ad = XXOR(a, d);
	byte bd = XXOR(b, d);
	byte da = XXOR(d, a);
	byte db = XXOR(d, b);
	byte cd = XXOR(c, d);
	byte dc = XXOR(d, c);

	byte _a = 0;
	byte _b = 0;
	predict(c, &_a, &_b);
	cout << endl;*/

	for (byte var1 = BYTE_MIN; var1 < BYTE_MAX; var1++) {
		for (byte var2 = BYTE_MIN; var2 < BYTE_MAX; var2++) {
			//byte var3 = XXOR(var1, var2);
			byte var3 = mix(var1, var2);

			byte _var1 = 0;
			byte _var2 = 0;
			//bool successful = predict(var3, &_var1, &_var2);
			bool successful = unmix(var3, &_var1, &_var2);

			if (successful) {
				if (var1 != _var1 || var2 != _var2) {
					cout << "var1 = " << (int)var1 << ", _var1 = " << (int)_var1 << ", var2 = " << (int)var2 << ", _var2 = " << (int)_var2 << ", var3 = " << (int)var3 << endl;
				}
			}

			cout << "var3 = " << (int)XXOR(var1, var2) << endl;
		}
	}

	system("pause");

	return 0;
}