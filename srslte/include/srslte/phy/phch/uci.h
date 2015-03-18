/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2014 The libLTE Developers. See the
 * COPYRIGHT file at the top-level directory of this distribution.
 *
 * \section LICENSE
 *
 * This file is part of the libLTE library.
 *
 * libLTE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * libLTE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * A copy of the GNU Lesser General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */


#ifndef UCI_
#define UCI_

#include "srslte/config.h"
#include "srslte/phy/common/phy_common.h"
#include "srslte/phy/phch/harq.h"
#include "srslte/phy/fec/crc.h"

#define MAX_CQI_LEN_PUSCH       512
#define MAX_CQI_LEN_PUCCH       13
#define CQI_CODED_PUCCH_B       20


typedef struct LIBLTE_API {
  crc_t crc;
  uint8_t tmp_cqi[MAX_CQI_LEN_PUSCH];
  uint8_t encoded_cqi[3*MAX_CQI_LEN_PUSCH];
} uci_cqi_pusch_t;

typedef struct LIBLTE_API {
  uint8_t *uci_cqi;
  uint32_t uci_cqi_len;
  float beta_cqi;
  uint8_t uci_ri;  // Only 1-bit supported for RI
  uint32_t uci_ri_len;
  float beta_ri;
  uint8_t uci_ack; // Only 1-bit supported for HARQ
  uint32_t uci_ack_len;
  float beta_ack;
} uci_data_t;

LIBLTE_API int uci_cqi_init(uci_cqi_pusch_t *q);

LIBLTE_API void uci_cqi_free(uci_cqi_pusch_t *q);

LIBLTE_API int uci_encode_cqi_pusch(uci_cqi_pusch_t *q, 
                                    uint8_t *cqi_data, 
                                    uint32_t cqi_len, 
                                    float beta, 
                                    uint32_t Q_prime_ri, 
                                    harq_t *harq_process, 
                                    uint8_t *q_bits);

LIBLTE_API int uci_encode_cqi_pucch(uint8_t *cqi_data, 
                                    uint32_t cqi_len, 
                                    uint8_t b_bits[CQI_CODED_PUCCH_B]);

LIBLTE_API int uci_encode_ack(uint8_t data,
                              uint32_t O_cqi,
                              float beta, 
                              harq_t *harq_process,
                              uint32_t H_prime_total, 
                              uint8_t *q_bits); 

LIBLTE_API int uci_encode_ri(uint8_t data,
                             uint32_t O_cqi,
                             float beta, 
                             harq_t *harq_process,
                             uint32_t H_prime_total, 
                             uint8_t *q_bits); 


#endif