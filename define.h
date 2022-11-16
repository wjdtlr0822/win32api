#pragma once

#define SINGLE(type) static type GetInst() { static type p; return &p;}