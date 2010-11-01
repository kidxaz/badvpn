/**
 * @file OTPGenerator.h
 * @author Ambroz Bizjak <ambrop7@gmail.com>
 * 
 * @section LICENSE
 * 
 * This file is part of BadVPN.
 * 
 * BadVPN is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 * 
 * BadVPN is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 * @section DESCRIPTION
 * 
 * Object which generates OTPs for use in sending packets.
 */

#ifndef BADVPN_SECURITY_OTPGENERATOR_H
#define BADVPN_SECURITY_OTPGENERATOR_H

#include <misc/debug.h>
#include <security/OTPCalculator.h>
#include <system/DebugObject.h>

/**
 * Object which generates OTPs for use in sending packets.
 */
typedef struct {
    DebugObject d_obj;
    int num_otps;
    int position;
    OTPCalculator calc;
    otp_t *otps;
} OTPGenerator;

/**
 * Initializes the generator.
 * The object is initialized with number of used OTPs = num_otps.
 *
 * @param g the object
 * @param num_otps number of OTPs to generate from a seed. Must be >=0.
 * @param cipher encryption cipher for calculating the OTPs. Must be valid
 *               according to {@link BEncryption_cipher_valid}.
 * @return 1 on success, 0 on failure
 */
int OTPGenerator_Init (OTPGenerator *g, int num_otps, int cipher) WARN_UNUSED;

/**
 * Frees the generator.
 *
 * @param g the object
 */
void OTPGenerator_Free (OTPGenerator *g);

/**
 * Assigns a seed to use for generating OTPs.
 * Sets the number of used OTPs to 0.
 *
 * @param g the object
 * @param key encryption key
 * @param iv initialization vector
 */
void OTPGenerator_SetSeed (OTPGenerator *g, uint8_t *key, uint8_t *iv);

/**
 * Returns the number of OTPs used up from the current seed so far.
 * If there is no seed yet, returns num_otps.
 *
 * @param g the object
 * @return number of used OTPs
 */
int OTPGenerator_GetPosition (OTPGenerator *g);

/**
 * Sets the number of used OTPs to num_otps.
 *
 * @param g the object
 */
void OTPGenerator_Reset (OTPGenerator *g);

/**
 * Generates a single OTP.
 * The number of used OTPs must be < num_otps.
 * The number of used OTPs is incremented.
 *
 * @param g the object
 */
otp_t OTPGenerator_GetOTP (OTPGenerator *g);

#endif